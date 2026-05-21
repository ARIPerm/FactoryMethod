#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <QObject>
#include "Factory/dataprocessor.h"

class FileProcessor : public QObject, DataProcessor
{
    Q_OBJECT
public:
    explicit FileProcessor(QObject *parent = nullptr);

    QScopedPointer<IDataLoader> createLoader() override;

signals:


};

#endif // FILEPROCESSOR_H
