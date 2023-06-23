#include "EventLogin.h"

EventLogin::EventLogin() {}

EventLogin::EventLogin(CacheUser* cacheUser, CachePlayer* cachePlayer) : pCacheUser(cacheUser), pCachePlayer(cachePlayer) {}

EventLogin::~EventLogin() {}

void EventLogin::Notify(ClientNode* Client) {}

void EventLogin::Response(ClientNode* Client) {}

void EventLogin::Request(ClientNode* Client, BYTE* Body, size_t BodyLen)
{

}
