#ifndef NETWORKPROCESSOR_H
#define NETWORKPROCESSOR_H

#include <QObject>
#include <Factory/dataprocessor.h>

class NetworkProcessor : public QObject, public DataProcessor
{
    Q_OBJECT
public:
    explicit NetworkProcessor(QObject *parent = nullptr);

    std::unique_ptr<IDataLoader> createLoader() override;

signals:
};

#endif // NETWORKPROCESSOR_H
