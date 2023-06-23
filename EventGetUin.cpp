#include "EventGetUin.h"

EventGetUin::EventGetUin() {}

EventGetUin::EventGetUin(CacheUser* cacheUser, CachePlayer* cachePlayer) : pCacheUser(cacheUser), pCachePlayer(cachePlayer) {}

EventGetUin::~EventGetUin() {}

void EventGetUin::Notify(ClientNode* Client) {}

void EventGetUin::Response(ClientNode* Client) {}

void EventGetUin::Response(ClientNode* Client, UINT Uin)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0);
	Write32(p, Uin);

	len = p - buf;
	SendToClient(Client, 1, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, MsgType::Response);
}

void EventGetUin::Request(ClientNode* Client, BYTE* Body, size_t BodyLen)
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

	UINT Uin = 0;
	BOOL isCmpPwd = false;

	if (pCacheUser != nullptr && pCachePlayer != nullptr)
	{
		Uin = pCacheUser->GetUinByUser(UserName);
		isCmpPwd = pCacheUser->cmpPassword(Uin, Password);
	}

	if (isCmpPwd)
	{
		printf("[LOGIN_SUCCESS]account:%s password:%s\n", UserName, Password);
		Response(Client, Uin);
	}
	else
	{
		/*
		* if the password is incorrect, return 0
		* If the UIN is 0, you cannot enter the game
		* There is a vulnerability here and there is no determination of whether the account is online
		*/
		printf("[LOGIN_FAILED]account:%s password:%s\n", UserName, Password);
		Response(Client, 0);
	}
	delete[] UserName;
	delete[] Password;
}