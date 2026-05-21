#ifndef NETWORKPROCESSOR_H
#define NETWORKPROCESSOR_H

#include <QObject>

class NetworkProcessor : public QObject
{
    Q_OBJECT
public:
    explicit NetworkProcessor(QObject *parent = nullptr);

signals:
};

#endif // NETWORKPROCESSOR_H
