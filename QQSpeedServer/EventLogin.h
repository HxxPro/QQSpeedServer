#pragma once
#include "EventWorld.h"
class EventLogin : public EventWorld
{
private:
	CacheUser* pCacheUser = nullptr;
	CachePlayer* pCachePlayer = nullptr;

public:
	EventLogin();
	EventLogin(CacheUser* cacheUser, CachePlayer* cachePlayer);
	~EventLogin();

	void Notify(ClientNode* Client);
	void Response(ClientNode* Client);
	void Request(ClientNode* Client, BYTE* Body, size_t BodyLen);
};

