#include "sqlloader.h"
#include <QList>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDebug>

SqlLoader::SqlLoader(QObject *parent)
    : QObject{parent}
{}

QList<QString> SqlLoader::load(QString path)
{
    QList<QString> result;
    if(!createDatabase(path))
        return result;

    if (path.isEmpty()) {
        qDebug() << "SqlLoader::load: Пустой путь к базе данных";
        return result;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open()) {
        qDebug() << "Ошибка октрытия базы данных:" << db.lastError().text();
        return result;
    }

    QSqlQuery query;
    if (!query.exec("SELECT value FROM data")) {
        qDebug() << "Запрос завершился с ошибкой:" << query.lastError().text();
        db.close();
        return result;
    }

    while (query.next()) {
        QString value = query.value(0).toString();
        if (!value.isEmpty()) {
            result.append(value);
        }
    }

    db.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);

    return result;
}

bool SqlLoader::createDatabase(QString path)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open()) {
        qDebug() << "SqlLoader::createDatabase не получилось открыть базу данных:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    QString createTableQuery =
        "CREATE TABLE IF NOT EXISTS data ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "value TEXT NOT NULL, "
        "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
        ")";

    if (!query.exec(createTableQuery)) {
        qDebug() << "Ошибка в создании таблицы:" << query.lastError().text();
        db.close();
        return false;
    }

    QStringList testData = {
        "Apple", "Banana", "Cherry", "Date", "Elderberry"
    };

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO data (value) VALUES (?)");

    for (const QString& value : testData) {
        insertQuery.bindValue(0, value);
        if (!insertQuery.exec()) {
            qDebug() << "Ошибка вставки данных в таблицу:" << insertQuery.lastError().text();
            return false;
        }
    }

    db.close();
    qDebug() << "База данных успешно создана:" << path;
    return true;
}