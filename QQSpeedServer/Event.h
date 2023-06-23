#pragma once
#include "Message.h"

#define MAX_DIR_LISTEN_PORT_NUM 3
#define ChatRoomNum 5

class Event : public MMSG
{
public:
	virtual void Notify(ClientNode* Client) = 0;
	virtual void Response(ClientNode* Client) = 0;
	virtual void Request(ClientNode* Client, BYTE* Body, size_t BodyLen) = 0;
};

