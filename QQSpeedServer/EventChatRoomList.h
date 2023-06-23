#pragma once
#include "EventWorld.h"

class EventChatRoomList : public EventWorld
{
private:
	CacheUser* pCacheUser = nullptr;
	CachePlayer* pCachePlayer = nullptr;

public:
	EventChatRoomList();
	EventChatRoomList(CacheUser* cacheUser, CachePlayer* cachePlayer);
	~EventChatRoomList();

	void Notify(ClientNode* Client);
	void Response(ClientNode* Client);
	void Response(ClientNode* Client, USHORT GetRoomType);
	void Request(ClientNode* Client, BYTE* Body, size_t BodyLen);
};

