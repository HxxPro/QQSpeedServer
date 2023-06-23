#pragma once
#include "Event.h"
class EventGetUin : public Event
{
private:
	CacheUser* pCacheUser = nullptr;
	CachePlayer* pCachePlayer = nullptr;

public:
	EventGetUin();
	EventGetUin(CacheUser* cacheUser, CachePlayer* cachePlayer);
	~EventGetUin();

	void Notify(ClientNode* Client);
	void Response(ClientNode* Client);
	void Response(ClientNode* Client, UINT Uin);
	void Request(ClientNode* Client, BYTE* Body, size_t BodyLen);
};

