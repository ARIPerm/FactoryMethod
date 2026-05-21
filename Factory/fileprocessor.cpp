#include "fileprocessor.h"
#include "Loaders/fileloader.h"

FileProcessor::FileProcessor(QObject *parent)
    : QObject{parent}, DataProcessor()
{}

std::unique_ptr<IDataLoader> FileProcessor::createLoader()
{
    return std::make_unique<FileLoader>(this);
}
