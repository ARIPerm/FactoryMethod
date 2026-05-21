#ifndef SQLPROCESSOR_H
#define SQLPROCESSOR_H

#include <QObject>

class SqlProcessor : public QObject
{
    Q_OBJECT
public:
    explicit SqlProcessor(QObject *parent = nullptr);

signals:
};

#endif // SQLPROCESSOR_H
