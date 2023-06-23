#pragma once
#include "Message.h"

class Event : public MMSG
{
public:
	virtual void Notify(ClientNode* Client) = 0;
	virtual void Response(ClientNode* Client) = 0;
	virtual void Request(ClientNode* Client, BYTE* Body, size_t BodyLen) = 0;
};

