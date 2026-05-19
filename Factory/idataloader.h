#ifndef IDATALOADER_H
#define IDATALOADER_H

#include <QList>

class IDataLoader
{
public:
    virtual ~IDataLoader() = default;

    virtual QList<QString> load(QString path) = 0;
};

#endif // IDATALOADER_H
