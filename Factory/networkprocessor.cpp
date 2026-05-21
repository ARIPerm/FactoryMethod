#include "networkprocessor.h"
#include "Loaders/networkloader.h"

NetworkProcessor::NetworkProcessor(QObject *parent)
    : QObject{parent}, DataProcessor()
{}

std::unique_ptr<IDataLoader> NetworkProcessor::createLoader()
{
    return std::make_unique<NetworkLoader>(this);
}
