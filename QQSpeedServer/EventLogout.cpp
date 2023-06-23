#include "EventLogout.h"

EventLogout::EventLogout() {}

EventLogout::EventLogout(CacheUser* cacheUser, CachePlayer* cachePlayer) : pCacheUser(cacheUser), pCachePlayer(cachePlayer) {}

EventLogout::~EventLogout() {}

void EventLogout::Notify(ClientNode* Client) {}

void EventLogout::Response(ClientNode* Client)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID
	Write8(p, 0); //ReasonLen

	len = p - buf;
	SendToClient(Client, 101, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, MsgType::Response);
}

void EventLogout::Request(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	UINT LogOutFlag = Read32(Body);
	int ServerKickReason = Read32(Body);

	Response(Client);
	Client->Server->Disconnect(Client->ConnID);
}
