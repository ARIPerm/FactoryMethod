#include "sqlprocessor.h"

SqlProcessor::SqlProcessor(QObject *parent)
    : QObject{parent}
{}

QScopedPointer<IDataLoader> SqlProcessor::createLoader()
{
    return QScopedPointer<SqlProcessor>(new SqlProcessor());
}
