#ifndef SQLLOADER_H
#define SQLLOADER_H

#include <QObject>
#include "Loaders/idataloader.h"

class SqlLoader : public QObject, public IDataLoader
{
    Q_OBJECT
public:
    explicit SqlLoader(QObject *parent = nullptr);

    QList<QString> load(QString path) override;

private:
    bool createDatabase(QString path);
};

#endif // SQLLOADER_H
