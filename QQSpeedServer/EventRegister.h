#pragma once
#include "Event.h"
class EventRegister : public Event
{
private:
	CacheUser* pCacheUser = nullptr;
	CachePlayer* pCachePlayer = nullptr;

public:
	EventRegister();
	EventRegister(CacheUser* cacheUser, CachePlayer* cachePlayer);
	~EventRegister();

	void Notify(ClientNode* Client);
	void Response(ClientNode* Client);
	void Response(ClientNode* Client, USHORT Result);
	void Request(ClientNode* Client, BYTE* Body, size_t BodyLen);
};

