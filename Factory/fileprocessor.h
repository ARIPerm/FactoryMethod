#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <QObject>
#include <memory>
#include "Factory/dataprocessor.h"

class FileProcessor : public QObject, public DataProcessor
{
    Q_OBJECT
public:
    explicit FileProcessor(QObject *parent = nullptr);

    std::unique_ptr<IDataLoader> createLoader() override;

signals:


};

#endif // FILEPROCESSOR_H
