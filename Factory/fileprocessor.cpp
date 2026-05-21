#include "fileprocessor.h"

FileProcessor::FileProcessor(QObject *parent)
    : QObject{parent}
{}

QScopedPointer<IDataLoader> FileProcessor::createLoader()
{

}
