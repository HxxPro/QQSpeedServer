#pragma once
#include "Event.h"
class EventWorldInfo : public Event
{
private:
	CacheUser* pCacheUser = nullptr;
	CachePlayer* pCachePlayer = nullptr;

public:
	EventWorldInfo();
	EventWorldInfo(CacheUser* cacheUser, CachePlayer* cachePlayer);
	~EventWorldInfo();

	void Notify(ClientNode* Client);
	void Response(ClientNode* Client);
	void Request(ClientNode* Client, BYTE* Body, size_t BodyLen);
};

