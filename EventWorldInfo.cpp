#include "EventWorldInfo.h"

EventWorldInfo::EventWorldInfo() {}

EventWorldInfo::EventWorldInfo(CacheUser* cacheUser, CachePlayer* cachePlayer) : pCacheUser(cacheUser), pCachePlayer(cachePlayer) {}

EventWorldInfo::~EventWorldInfo() {}

void EventWorldInfo::Notify(ClientNode* Client) {}

void EventWorldInfo::Response(ClientNode* Client) {}

void EventWorldInfo::Request(ClientNode* Client, BYTE* Body, size_t BodyLen)
{

}
