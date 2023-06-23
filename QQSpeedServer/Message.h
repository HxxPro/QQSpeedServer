#pragma once
#include "stdafx.h"

#include "CacheUser.h"
#include "CachePlayer.h"

struct Message
{
	USHORT MsgID;
	BYTE* Body;
	size_t BodyLen;

	CacheUser* pCacheUser = nullptr;
	CachePlayer* pCachePlayer = nullptr;

	Message(USHORT msgID, BYTE* body, size_t bodyLen, CacheUser* cacheUser, CachePlayer* cachePlayer);
};

class MMSG
{
public:
	bool SendToClient(ClientNode* Client, short MsgID, const BYTE* Data, DWORD Length, short SrcID, char SrcFE, short DstID, short MsgType, char Encrypt = true);
};