#include "networkloader.h"
#include <QEventLoop>
#include <QJsonParseError>
#include <QXmlStreamReader>
#include <QJsonObject>
#include <QJsonArray>

NetworkLoader::NetworkLoader(QObject *parent)
    : QObject{parent}, _pNetworkManager(new QNetworkAccessManager(this)), _timeoutMs(30000)
{}

NetworkLoader::~NetworkLoader()
{
    for (RequestContext *context : _pActiveRequests) {
        if (context->reply) {
            context->reply->abort();
            context->reply->deleteLater();
        }
        if (context->timer) {
            context->timer->stop();
            delete context->timer;
        }
        delete context;
    }
    _pActiveRequests.clear();
}

QList<QString> NetworkLoader::load(QString path)
{
    if (path.isEmpty()) {
        qWarning() << "NetworkLoader::load: путь пустой";
        return QList<QString>();
    }

    RequestContext *context = new RequestContext();
    _pActiveRequests.append(context);

    QUrl url(path);

    if (url.scheme().isEmpty()) {
        url = QUrl("http://" + path);
    }

    performHttpRequest(url, context);

    QEventLoop loop;
    connect(context->timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    if (context->reply) {
        connect(context->reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    }
    loop.exec();

    QList<QString> result = context->result;
    if (!context->isSuccess) {
        qWarning() << "NetworkLoader::load провал:" << context->errorMessage;
    }

    _pActiveRequests.removeOne(context);
    delete context;

    return result;
}

void NetworkLoader::performHttpRequest(const QUrl &url, RequestContext *context)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader,
                      "Mozilla/5.0 (QtNetworkLoader)");
    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute,
                         QNetworkRequest::NoLessSafeRedirectPolicy);


    context->reply = _pNetworkManager->get(request);
    if (!context->reply) {
        context->isSuccess = false;
        context->errorMessage = "Ошибка в попытке создать реквест (ошибка сети)";
        context->isCompleted = true;
        return;
    }

    context->timer = new QTimer(this);
    context->timer->setSingleShot(true);
    connect(context->timer, &QTimer::timeout, this, &NetworkLoader::onTimeout);
    context->timer->start(_timeoutMs);

    context->reply->setProperty("requestContext", QVariant::fromValue((void*)context));

    connect(context->reply, &QNetworkReply::finished,
            this, &NetworkLoader::onRequestFinished);
}

QList<QString> NetworkLoader::parseData(const QByteArray &data, const QString &contentType)
{
    if (data.isEmpty()) {
        return QList<QString>();
    }

    if (isJsonFormat(contentType, data)) {
        return parseJson(data);
    }

    if (isXmlFormat(contentType, data)) {
        return parseXml(data);
    }

    QList<QString> result = parseJson(data);
    if (!result.isEmpty()) {
        return result;
    }

    result = parseXml(data);
    if (!result.isEmpty()) {
        return result;
    }

    qWarning() << "Не известный формат, распарсить не получилось";
    return QList<QString>();
}

QList<QString> NetworkLoader::parseJson(const QByteArray &data)
{
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << parseError.errorString();
        return QList<QString>();
    }

    QList<QString> result;

    if (doc.isObject()) {
        extractStringsFromJson(doc.object(), result);
    } else if (doc.isArray()) {
        extractStringsFromJson(doc.array(), result);
    }

    return result;
}

QList<QString> NetworkLoader::parseXml(const QByteArray &data)
{
    QXmlStreamReader xml(data);
    QList<QString> result;

    while (!xml.atEnd() && !xml.hasError()) {
        xml.readNext();

        if (xml.isCharacters() && !xml.isWhitespace()) {
            QString text = xml.text().toString().trimmed();
            if (!text.isEmpty()) {
                result.append(text);
            }
        }
    }

    if (xml.hasError()) {
        qWarning() << "XML parse error:" << xml.errorString();
        return QList<QString>();
    }

    return result;
}

void NetworkLoader::extractStringsFromJson(const QJsonValue &value, QList<QString> &result)
{
    if (value.isString()) {
        result.append(value.toString());
    }
    else if (value.isObject()) {
        QJsonObject obj = value.toObject();
        for (auto it = obj.begin(); it != obj.end(); ++it) {
            extractStringsFromJson(it.value(), result);
        }
    }
    else if (value.isArray()) {
        QJsonArray array = value.toArray();
        for (const QJsonValue &item : array) {
            extractStringsFromJson(item, result);
        }
    }
}

bool NetworkLoader::isJsonFormat(const QString &contentType, const QByteArray &data)
{
    QString ct = contentType.toLower();
    if (ct.contains("json")) {
        return true;
    }

    QString trimmed = QString::fromUtf8(data).trimmed();
    if (trimmed.startsWith('{') || trimmed.startsWith('[')) {
        return true;
    }

    return false;
}

bool NetworkLoader::isXmlFormat(const QString &contentType, const QByteArray &data)
{
    QString ct = contentType.toLower();
    if (ct.contains("xml") || ct.contains("rss") || ct.contains("atom")) {
        return true;
    }

    QString trimmed = QString::fromUtf8(data).trimmed();
    if (trimmed.startsWith('<')) {
        return true;
    }

    return false;
}

void NetworkLoader::onRequestFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply)
        return;

    void *ptr = reply->property("requestContext").value<void*>();
    RequestContext *context = static_cast<RequestContext*>(ptr);
    if (!context)
        return;

    if (context->timer) {
        context->timer->stop();
    }

    if (reply->error() != QNetworkReply::NoError) {
        context->isSuccess = false;
        context->errorMessage = QString("Network error: %1").arg(reply->errorString());
        context->isCompleted = true;
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    QString contentType = reply->header(QNetworkRequest::ContentTypeHeader).toString();

    context->result = parseData(data, contentType);
    context->isSuccess = !context->result.isEmpty();
    context->isCompleted = true;

    if (!context->isSuccess) {
        context->errorMessage = "Ошибка при парсинге данных";
    }

    reply->deleteLater();
}

void NetworkLoader::onTimeout()
{
    QTimer *timer = qobject_cast<QTimer*>(sender());
    if (!timer)
        return;

    RequestContext *context = nullptr;
    for (RequestContext *ctx : _pActiveRequests) {
        if (ctx->timer == timer) {
            context = ctx;
            break;
        }
    }

    if (!context)
        return;

    if (context->isCompleted)
        return;

    if (context->reply) {
        context->reply->abort();
        context->reply->deleteLater();
        context->reply = nullptr;
    }

    context->isSuccess = false;
    context->errorMessage = QString("Запрос истек со временем ожидания %1 ms").arg(_timeoutMs);
    context->isCompleted = true;
}
