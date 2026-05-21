#include "fileloader.h"

FileLoader::FileLoader(QObject *parent)
    : QObject{parent}
{}

QList<QString> FileLoader::load(QString path)
{
    QList<QString> result;

    if (path.isEmpty()) {
        qDebug() << "FileLoader::load: Путь пустой";
        return result;
    }

    QFile file(path);
    if (!file.exists()) {
        qDebug() << "Ошибка: Файл не открыт:" << path;
        return result;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка: файл не получилось открыть для чтения:" << path;
        qDebug() << "Детали ошибки:" << file.errorString();
        return result;
    }

    QTextStream stream(&file);
    stream.setCodec("UTF-8");

    while (!stream.atEnd()) {
        QString line = stream.readLine();

        if (!line.trimmed().isEmpty())
            result.append(line);
    }

    file.close();

    return result;
}
