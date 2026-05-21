#include "dataprocessor.h"

QList<QString> DataProcessor::loadData(const QString &path)
{
    auto loader = createLoader();
    if (loader) {
        return loader->load(path);
    }
    return QList<QString>();
}
