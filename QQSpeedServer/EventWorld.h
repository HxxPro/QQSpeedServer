#pragma once
#include "Event.h"


struct Map
{
	UINT Head;
	UINT End;
	UINT Round;
	bool Loop;
};
struct Item
{
	UINT ID;
	UINT Type;
};
enum ItemType
{
	EAIT_Unknown,
	EAIT_CAR,
	EAIT_PET
};
enum ServerType
{
	Game,
	Dance,
	Relax
};

struct DirServerInfo
{
	int ServerID;
	USHORT LocationID;
	UINT ServerIP;
	USHORT ServerPort[MAX_DIR_LISTEN_PORT_NUM];
	void* MultiIPInfo;
};
struct WorldBaseInfo
{
	BYTE WorldID;
	char Name[256];
	BYTE DirNum;
	DirServerInfo* Dir;
};
struct GameServerInfo
{
	int ServerID;
	UINT ServerIP;
	USHORT TcpPort;
	USHORT UdpPort;
	USHORT MaxPlayerNum;
	USHORT CurrentPlayerNum;
	UINT RandomKey;
	BYTE IsDisabledLogin;
	void* MultiIPInfo;
};
struct IDCServerInfo
{
	USHORT LocationID;
	BYTE GameServerNum;
	GameServerInfo* GameServer;
};
struct ChannelInfo
{
	BYTE ChannelID;
	BYTE IDCNum;
	IDCServerInfo* IDC;
};
struct CountryInfo
{
	BYTE CountryID;
	BYTE ChannelNum;
	ChannelInfo* Channel;
};
struct ShopServerInfo
{
	int ServerID;
	USHORT LocationID;
	UINT ServerIP;
	USHORT ServerPort;
};

struct
{
	GameServerInfo ServerInfo;
	USHORT LocationID;
} g_BorderServerInfo;
struct
{
	GameServerInfo ServerInfo;
	USHORT LocationID;
} g_MatchServerInfo;
struct
{
	GameServerInfo ServerInfo;
	USHORT LocationID;
} g_RelaxServerInfo;
struct
{
	GameServerInfo ServerInfo;
	USHORT LocationID;
} g_TeamServerInfo;
struct
{
	GameServerInfo ServerInfo;
	USHORT LocationID;
} g_DanceServerInfo;
struct
{
	GameServerInfo ServerInfo;
	USHORT LocationID;
} g_SlideServerInfo;

struct ChatRoomNode
{
	UINT ID;
	const char* Name;
	short CurrPlayerNum;
	short MaxPlayerNum;
	int RoomType;
	short SceneID;
	int x;
	int y;
	int z;
	ClientNode* Player[99];
};

struct ItemInfo
{
	UINT ItemID;
	int ItemNum;
	int AvailPeriod;
	bool Status;
	int ObtainTime;
	int OtherAttribute;
	int ItemType;
};

class EventWorld : public Event
{
private:
	std::map<UINT, Map*> Maps;
	std::map<UINT, Item*> Items;

	UINT IP;
	USHORT TcpPort;
	USHORT UdpPort;
	string ServerName;
	const char* Name;

public:
	WorldBaseInfo g_WorldBaseInfo;
	CountryInfo g_CountryInfo;
	ShopServerInfo g_ShopServerInfo;
	ChatRoomNode ChatRooms[ChatRoomNum];

	EventWorld();
	~EventWorld();


	virtual void Notify(ClientNode* Client) = 0;
	virtual void Response(ClientNode* Client) = 0;
	virtual void Request(ClientNode* Client, BYTE* Body, size_t BodyLen) = 0;

	Map* GetMap(UINT ID);
	UINT GetItemType(UINT ID);
	int GetServerType(int ServerID);

private:
	void InitDirServer();
	void InitChatRoom();
};

