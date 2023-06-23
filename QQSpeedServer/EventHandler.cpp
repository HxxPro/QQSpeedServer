#include "EventHandler.h"

#include "EventGetUin.h"
#include "EventRegister.h"
#include "EventWorldInfo.h"
#include "EventChatRoomList.h"
#include "EventLogin.h"
#include "EventLogout.h"


void UserEventHandler::HandleMessage(ClientNode* Client, const Message& message)
{
    printf("UserEvent MsgID:%d\n", message.MsgID);
    switch (message.MsgID)
    {
    case 1:
    {
        EventGetUin getuin(message.pCacheUser, message.pCachePlayer);
        getuin.Request(Client, message.Body, message.BodyLen);
        break;
    }
    case 2:
    {
        EventRegister reg(message.pCacheUser, message.pCachePlayer);
        reg.Request(Client, message.Body, message.BodyLen);
        break;
    }
    }
}

void PlayerEventHandler::HandleMessage(ClientNode* Client, const Message& message)
{
    printf("PlayerEvent MsgID:%d\n", message.MsgID);
    switch (message.MsgID)
    {
    case 100:
    {
        EventLogin login(message.pCacheUser, message.pCachePlayer);
        login.Request(Client, message.Body, message.BodyLen);
        break;
    }
    case 101:
    {
        EventLogout logout(message.pCacheUser, message.pCachePlayer);
        logout.Request(Client, message.Body, message.BodyLen);
        break;
    }
    }
}

void WorldEventHandler::HandleMessage(ClientNode* Client, const Message& message)
{
    printf("WorldEvent MsgID:%d\n", message.MsgID);
    switch (message.MsgID)
    {
    case 90:
    {
        EventWorldInfo worldinfo(message.pCacheUser, message.pCachePlayer);
        worldinfo.Request(Client, message.Body, message.BodyLen);
        break;
    }
    case 91:
    {
        EventChatRoomList chatroomlist(message.pCacheUser, message.pCachePlayer);
        chatroomlist.Request(Client, message.Body, message.BodyLen);
        break;
    }
    }
}
