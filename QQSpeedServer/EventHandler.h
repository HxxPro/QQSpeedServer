#pragma once
#include "Message.h"

class EventHandler
{
public:
	virtual void HandleMessage(ClientNode* Client, const Message& message) = 0;
};

class UserEventHandler : public EventHandler
{
public:
	void HandleMessage(ClientNode* Client, const Message& message) override;
};

class PlayerEventHandler : public EventHandler
{
public:
	void HandleMessage(ClientNode* Client, const Message& message) override;
};

class WorldEventHandler : public EventHandler
{
public:
	void HandleMessage(ClientNode* Client, const Message& message) override;
};
