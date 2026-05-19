#ifndef SQLLOADER_H
#define SQLLOADER_H

#include <QObject>
#include "Factory/idataloader.h"

class SqlLoader : public QObject, IDataLoader
{
    Q_OBJECT
public:
    explicit SqlLoader(QObject *parent = nullptr);

    QList<QString> load(QString path) override;

signals:

    // IDataLoader interface
};

#endif // SQLLOADER_H
