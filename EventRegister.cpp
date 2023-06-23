#include "EventRegister.h"

EventRegister::EventRegister() {}

EventRegister::EventRegister(CacheUser* cacheUser, CachePlayer* cachePlayer) : pCacheUser(cacheUser), pCachePlayer(cachePlayer) {}

EventRegister::~EventRegister() {}

void EventRegister::Notify(ClientNode* Client) {}

void EventRegister::Response(ClientNode* Client) {}

void EventRegister::Response(ClientNode* Client, USHORT Result)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, Result);

	len = p - buf;

	SendToClient(Client, 2, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, MsgType::Response);
}

void EventRegister::Request(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	size_t len;

	len = Read8(Body);
	char* UserName = new char[len + 1];
	memcpy(UserName, Body, len);
	Body += len;
	UserName[len] = 0;

	len = Read8(Body);
	char* Password = new char[len + 1];
	memcpy(Password, Body, len);
	Body += len;
	Password[len] = 0;

	bool Result = false;
	if (pCacheUser != nullptr && pCachePlayer != nullptr)
	{
		Result = pCacheUser->Register(UserName, Password);
	}

	if (Result)
	{
		printf("[REGISTER_SUCCESS]account:%s, password:%s\n", UserName, Password);
	}
	else
	{
		printf("[REGISTER_FAILED]account:%s, password:%s\n", UserName, Password);
	}

	delete[] UserName;
	delete[] Password;

	Response(Client, !Result);
}
