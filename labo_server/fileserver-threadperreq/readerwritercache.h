#ifndef READERWRITERCACHE_H
#define READERWRITERCACHE_H
#include <QHash>
#include <QThread>
#include <QDateTime>
#include <QMutex>
#include "option.h"
#include "request.h"
#include "response.h"
#include "readerwriterlock.h"

class ReaderWriterCache
{
private:
	struct TimestampedResponse {
		Response response;
		long timestamp;
	};

	class InvalidationTimer: public QThread {
		friend ReaderWriterCache;

	private:
		ReaderWriterCache* cache;

	public:
		InvalidationTimer(ReaderWriterCache* cache): cache(cache) {}

	protected:
        void run(){
            QHash<QString, TimestampedResponse>::iterator it;
            long currentTime;

            for(it = cache->map->begin(); it != cache->map->end(); it++){
                currentTime = QDateTime::currentDateTime().toString().toLong();
                if(((TimestampedResponse)it.value()).timestamp > currentTime + cache->staleDelaySec){

                    it = cache->map->erase(it);

                }
            }

        }
	};

    QHash<QString, TimestampedResponse>* map;
	int invalidationDelaySec;
	int staleDelaySec;
	InvalidationTimer* timer;
	ReaderWriterLock lock;

public:
	ReaderWriterCache(int invalidationDelaySec, int staleDelaySec);
    ~ReaderWriterCache();
	Option<Response> tryGetCachedResponse(Request& request);
	void putResponse(Response& response);
};

#endif // READERWRITERCACHE_H