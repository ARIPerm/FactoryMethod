#include "dataprocessor.h"

DataProcessor::DataProcessor() {}

QList<QString> DataProcessor::loadData(QString path)
{
    auto loader = const_cast<DataProcessor*>(this)->createLoader();
    return loader.data()->load(path);
}
