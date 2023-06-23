#pragma once
#include "EventWorld.h"

class EventWorldInfo : public EventWorld
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
	void Response(ClientNode* Client, UINT ClientVersion, UINT MasterVersion, UINT Slaveversion);
	void Request(ClientNode* Client, BYTE* Body, size_t BodyLen);
};

