#pragma once
#include "Event.h"
class EventLogout : public Event
{
private:
	CacheUser* pCacheUser = nullptr;
	CachePlayer* pCachePlayer = nullptr;

public:
	EventLogout();
	EventLogout(CacheUser* cacheUser, CachePlayer* cachePlayer);
	~EventLogout();

	void Notify(ClientNode* Client);
	void Response(ClientNode* Client);
	void Request(ClientNode* Client, BYTE* Body, size_t BodyLen);
};

