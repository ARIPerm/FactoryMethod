#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>
#include "Factory/idataloader.h"

class FileLoader : public QObject, IDataLoader
{
    Q_OBJECT
public:
    explicit FileLoader(QObject *parent = nullptr);

    QList<QString> load(QString path) override;

signals:
};

#endif // FILELOADER_H
