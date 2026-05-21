#include "networkprocessor.h"

NetworkProcessor::NetworkProcessor(QObject *parent)
    : QObject{parent}
{}

QScopedPointer<IDataLoader> NetworkProcessor::createLoader()
{

}
