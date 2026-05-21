#include "sqlprocessor.h"
#include "Loaders/sqlloader.h"

SqlProcessor::SqlProcessor(QObject *parent)
    : QObject{parent}, DataProcessor()
{}

std::unique_ptr<IDataLoader> SqlProcessor::createLoader()
{
    return std::make_unique<SqlLoader>(this);
}
