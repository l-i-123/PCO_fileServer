#include "readerwritercache.h"
#include "option.h"
#include <QDateTime>
#include <QList>
#include <QDebug>

ReaderWriterCache::ReaderWriterCache(int invalidationDelaySec, int staleDelaySec):
    invalidationDelaySec(invalidationDelaySec), staleDelaySec(staleDelaySec)
{
    timer = new InvalidationTimer(this);
    map = new QHash<QString, TimestampedResponse>();
}

ReaderWriterCache::~ReaderWriterCache()
{}

void ReaderWriterCache::putResponse(Response &response) {
    lock.lockWriting();
    TimestampedResponse timerResponse;
    timerResponse.timestamp = QDateTime::currentDateTime().toString().toLong();
    timerResponse.response = response;
    map->insert(response.getRequest().getFilePath(), timerResponse);
    lock.unlockWriting();
}

Option<Response> ReaderWriterCache::tryGetCachedResponse(Request &request) {
    InvalidationTimer timer(this);
    timer.run();
    lock.lockReading();
    QString keyValue = request.getFilePath();
    Option<Response> res = Option<Response>::none();

    if(map->contains(keyValue)){
        TimestampedResponse timerResponse = map->value(keyValue);
        res = Option<Response>::some(timerResponse.response);
    }

    lock.unlockReading();
    return res;
}
