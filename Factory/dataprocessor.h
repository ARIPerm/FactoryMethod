#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <memory>
#include "Loaders/idataloader.h"

class DataProcessor
{
public:
    virtual ~DataProcessor() = default;

    virtual std::unique_ptr<IDataLoader> createLoader() = 0;

    QList<QString> loadData(const QString& path);
};

#endif // DATAPROCESSOR_H
