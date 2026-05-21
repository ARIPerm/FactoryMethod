#ifndef NETWORKLOADER_H
#define NETWORKLOADER_H

#include <QObject>
#include <QNetworkReply>
#include <QTimer>
#include "Loaders/idataloader.h"

class NetworkLoader : public QObject, public IDataLoader
{
    Q_OBJECT
public:
    explicit NetworkLoader(QObject *parent = nullptr);
    ~NetworkLoader();

    QList<QString> load(QString path) override;

signals:

private:
    struct RequestContext {
        QNetworkReply *reply = nullptr;     // Объект ответа от сети
        QTimer *timer = nullptr;            // Таймер для контроля таймаута
        bool isCompleted = false;           // Флаг завершения запроса
        bool isSuccess = false;             // Флаг успешности
        QList<QString> result;              // Результат парсинга
        QString errorMessage;               // Сообщение об ошибке
    };

    QNetworkAccessManager *_pNetworkManager;
    QList<RequestContext*> _pActiveRequests;
    int _timeoutMs;

    void performHttpRequest(const QUrl &url, RequestContext *context);

    QList<QString> parseData(const QByteArray &data, const QString &contentType);
    QList<QString> parseJson(const QByteArray &data);
    QList<QString> parseXml(const QByteArray &data);

    void extractStringsFromJson(const QJsonValue &value, QList<QString> &result);

    bool isJsonFormat(const QString &contentType, const QByteArray &data);
    bool isXmlFormat(const QString &contentType, const QByteArray &data);

private slots:
    void onRequestFinished();
    void onTimeout();
};

#endif // NETWORKLOADER_H
