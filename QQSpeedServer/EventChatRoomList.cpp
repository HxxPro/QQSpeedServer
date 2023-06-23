#include "EventChatRoomList.h"

EventChatRoomList::EventChatRoomList() {}

EventChatRoomList::EventChatRoomList(CacheUser* cacheUser, CachePlayer* cachePlayer) : pCacheUser(cacheUser), pCachePlayer(cachePlayer) {}

EventChatRoomList::~EventChatRoomList() {}

void EventChatRoomList::Notify(ClientNode* Client) {}

void EventChatRoomList::Response(ClientNode* Client) {}

void EventChatRoomList::Response(ClientNode* Client, USHORT GetRoomType)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;


	Write16(p, 0); //ResultID
	Write8(p, 0); //ReasonLen
	Write16(p, 1); //CurTotalRoomNum
	Write16(p, 0); //StartRoomIdx

	Write16(p, ChatRoomNum); //ChatRoomNum
	for (size_t i = 0; i < ChatRoomNum; i++)
	{ //ChatRoomInfo
		BYTE* pChatRoomInfo = p;
		Write16(pChatRoomInfo, 0); //len

		Write32(pChatRoomInfo, g_RelaxServerInfo.ServerInfo.ServerID); //ServerID
		Write32(pChatRoomInfo, ChatRooms[i].ID); //ChatRoomID

		len = strlen(ChatRooms[i].Name);
		Write8(pChatRoomInfo, (BYTE)len); //RoomNameLen
		memcpy(pChatRoomInfo, ChatRooms[i].Name, len);
		pChatRoomInfo += len;

		Write16(pChatRoomInfo, ChatRooms[i].CurrPlayerNum); //CurrPlayerNum
		Write16(pChatRoomInfo, ChatRooms[i].MaxPlayerNum); //MaxPlayerNum

		Write32(pChatRoomInfo, ChatRooms[i].RoomType); //RoomType
		Write16(pChatRoomInfo, ChatRooms[i].SceneID); //SceneID
		Write16(pChatRoomInfo, 0); //CurrMaleNum

		len = pChatRoomInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write16(p, GetRoomType); //GetRoomType


	len = p - buf;
	SendToClient(Client, 91, buf, len, 0, FE_DIRSVRD, 0, MsgType::Response);
}

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
