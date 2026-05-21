#ifndef SQLPROCESSOR_H
#define SQLPROCESSOR_H

#include <QObject>
#include <memory>
#include "Factory/dataprocessor.h"


class SqlProcessor : public QObject, public DataProcessor
{
    Q_OBJECT
public:
    explicit SqlProcessor(QObject *parent = nullptr);

    std::unique_ptr<IDataLoader> createLoader() override;

signals:
};

#endif // SQLPROCESSOR_H
