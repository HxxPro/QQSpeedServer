#include "EventChatRoomList.h"

EventChatRoomList::EventChatRoomList() {}

EventChatRoomList::EventChatRoomList(CacheUser* cacheUser, CachePlayer* cachePlayer) : pCacheUser(cacheUser), pCachePlayer(cachePlayer) {}

EventChatRoomList::~EventChatRoomList() {}

void EventChatRoomList::Notify(ClientNode* Client) {}

void EventChatRoomList::Response(ClientNode* Client) {}

void EventChatRoomList::Response(ClientNode* Client, USHORT GetRoomType) {}

void EventChatRoomList::Request(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	USHORT StartRoomIdx = Read16(Body);
	USHORT GetRoomNum = Read16(Body);
	USHORT GetRoomType = Read16(Body);

	printf("GetRoomType:%d\n", GetRoomType);

	Response(Client, GetRoomType);
}
