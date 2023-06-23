#include "EventWorld.h"

#include <filesystem>

EventWorld::EventWorld()
{
#ifdef _DEBUG
	printf("==========================================WORLD LOADING==========================================\n");
#endif // _DEBUG

	try
	{
		YAML::Node Config_Map = YAML::LoadFile("Map.yml");
		YAML::Node Config_Item = YAML::LoadFile("Item.yml");
		YAML::Node Config_ipAddress = YAML::LoadFile("config.yml");

		for (size_t i = 0; i < Config_Map.size(); i++)
		{
			YAML::Node map = Config_Map[i];
			Map* pMap = new Map;
			Maps[map["ID"].as<UINT>()] = pMap;
			pMap->Head = map["Head"].as<UINT>();
			pMap->End = map["End"].as<UINT>();
			pMap->Loop = map["Loop"].as<bool>();
			pMap->Round = map["Round"].as<UINT>();
		}

		for (size_t i = 0; i < Config_Item.size(); i++)
		{
			YAML::Node item = Config_Item[i];
			Item* pItem = new Item;
			pItem->ID = item["ID"].as<UINT>();
			std::string Type = item["Type"].as<std::string>();
			pItem->Type = EAIT_Unknown;

			if (Type == "EAIT_CAR")
			{
				pItem->Type = EAIT_CAR;
			}
			if (Type == "EAIT_PET")
			{
				pItem->Type = EAIT_PET;
			}
			Items[pItem->ID] = pItem;
		}

		YAML::Node Server = Config_ipAddress["Server"];
		ServerName = Server["Name"].as<std::string>();
		IP = inet_addr(Server["IP"].as<std::string>().c_str());
		TcpPort = Server["TcpPort"].as<USHORT>();
		UdpPort = Server["UdpPort"].as<USHORT>();
		Name = ServerName.c_str();
	}
	catch (const std::exception&)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		std::cout << "An error occurred while loading the configuration file, Please check if the configuration file is correct...\n" << std::endl;

		std::filesystem::path currentPath = std::filesystem::current_path();
		std::cout << "Current directory: " << currentPath << std::endl;

		system("pause");
		exit(0);
	}

	InitDirServer();
	InitChatRoom();

#ifdef _DEBUG
	printf("==========================================WORLD SUCCESS==========================================\n");
	cout << "g_BorderServerInfo.ServerInfo.ServerIP: " << g_BorderServerInfo.ServerInfo.ServerIP << endl;
#endif // _DEBUG
}

EventWorld::~EventWorld()
{
}

Map* EventWorld::GetMap(UINT ID)
{
	return Maps[ID];
}

UINT EventWorld::GetItemType(UINT ID)
{
	Item* pItem = Items[ID];
	UINT Type = EAIT_Unknown;
	if (pItem)
	{
		Type = pItem->Type;
	}
	return Type;
}

int EventWorld::GetServerType(int ServerID)
{
	if (ServerID == g_RelaxServerInfo.ServerInfo.ServerID)
	{
		return Relax;
	}
	if (ServerID == g_DanceServerInfo.ServerInfo.ServerID)
	{
		return Dance;
	}
	return Game;
}

void EventWorld::InitDirServer()
{
	{
		g_WorldBaseInfo.WorldID = 1;

		strcpy_s(g_WorldBaseInfo.Name, Name);

		g_WorldBaseInfo.DirNum = 1;
		DirServerInfo* pDir = new DirServerInfo;
		g_WorldBaseInfo.Dir = pDir;
		{
			pDir->ServerID = 2;
			pDir->LocationID = 1;
			pDir->ServerIP = IP;
			pDir->ServerPort[0] = TcpPort;
			pDir->ServerPort[1] = TcpPort;
			pDir->ServerPort[2] = TcpPort;
			pDir->MultiIPInfo = nullptr;
		}
	}

	{
		g_CountryInfo.CountryID = 1;

		// 在 ZingSpeed 中必须确保有所有频道有相同的 LocationID, 否则无法登录!
		g_CountryInfo.ChannelNum = 5;
		ChannelInfo* pChannel = new ChannelInfo[5];
		g_CountryInfo.Channel = pChannel;
		{
			pChannel->ChannelID = 1; //新手
			pChannel->IDCNum = 1;
			IDCServerInfo* pIDC = new IDCServerInfo;
			pChannel->IDC = pIDC;
			{
				pIDC->LocationID = 1;
				pIDC->GameServerNum = 1;
				GameServerInfo* pGameServer = new GameServerInfo;
				pIDC->GameServer = pGameServer;
				{
					pGameServer->ServerID = 110;
					pGameServer->ServerIP = IP;
					pGameServer->TcpPort = TcpPort;
					pGameServer->UdpPort = UdpPort;
					pGameServer->MaxPlayerNum = 10000;
					pGameServer->CurrentPlayerNum = 1;
					pGameServer->RandomKey = 0;
					pGameServer->IsDisabledLogin = 0;
					pGameServer->MultiIPInfo = nullptr;
				}
			}
			pChannel++;
		}
		{
			pChannel->ChannelID = 2; //初级
			pChannel->IDCNum = 1;
			IDCServerInfo* pIDC = new IDCServerInfo;
			pChannel->IDC = pIDC;
			{
				pIDC->LocationID = 1;
				pIDC->GameServerNum = 1;
				GameServerInfo* pGameServer = new GameServerInfo;
				pIDC->GameServer = pGameServer;
				{
					pGameServer->ServerID = 111;
					pGameServer->ServerIP = IP;
					pGameServer->TcpPort = TcpPort;
					pGameServer->UdpPort = UdpPort;
					pGameServer->MaxPlayerNum = 10000;
					pGameServer->CurrentPlayerNum = 1;
					pGameServer->RandomKey = 0;
					pGameServer->IsDisabledLogin = 0;
					pGameServer->MultiIPInfo = nullptr;
				}
			}
			pChannel++;
		}
		{
			pChannel->ChannelID = 3; //中级
			pChannel->IDCNum = 1;
			IDCServerInfo* pIDC = new IDCServerInfo;
			pChannel->IDC = pIDC;
			{
				pIDC->LocationID = 1;
				pIDC->GameServerNum = 1;
				GameServerInfo* pGameServer = new GameServerInfo;
				pIDC->GameServer = pGameServer;
				{
					pGameServer->ServerID = 112;
					pGameServer->ServerIP = IP;
					pGameServer->TcpPort = TcpPort;
					pGameServer->UdpPort = UdpPort;
					pGameServer->MaxPlayerNum = 10000;
					pGameServer->CurrentPlayerNum = 1;
					pGameServer->RandomKey = 0;
					pGameServer->IsDisabledLogin = 0;
					pGameServer->MultiIPInfo = nullptr;
				}
			}
			pChannel++;
		}
		{
			pChannel->ChannelID = 4; //高级
			pChannel->IDCNum = 1;
			IDCServerInfo* pIDC = new IDCServerInfo;
			pChannel->IDC = pIDC;
			{
				pIDC->LocationID = 1;
				pIDC->GameServerNum = 1;
				GameServerInfo* pGameServer = new GameServerInfo;
				pIDC->GameServer = pGameServer;
				{
					pGameServer->ServerID = 113;
					pGameServer->ServerIP = IP;
					pGameServer->TcpPort = TcpPort;
					pGameServer->UdpPort = UdpPort;
					pGameServer->MaxPlayerNum = 10000;
					pGameServer->CurrentPlayerNum = 1;
					pGameServer->RandomKey = 0;
					pGameServer->IsDisabledLogin = 0;
					pGameServer->MultiIPInfo = nullptr;
				}
			}
			pChannel++;
		}
		{
			pChannel->ChannelID = 6; //交友
			pChannel->IDCNum = 1;
			IDCServerInfo* pIDC = new IDCServerInfo;
			pChannel->IDC = pIDC;
			{
				pIDC->LocationID = 1;
				pIDC->GameServerNum = 1;
				GameServerInfo* pGameServer = new GameServerInfo;
				pIDC->GameServer = pGameServer;
				{
					pGameServer->ServerID = 115;
					pGameServer->ServerIP = IP;
					pGameServer->TcpPort = TcpPort;
					pGameServer->UdpPort = UdpPort;
					pGameServer->MaxPlayerNum = 10000;
					pGameServer->CurrentPlayerNum = 1;
					pGameServer->RandomKey = 0;
					pGameServer->IsDisabledLogin = 0;
					pGameServer->MultiIPInfo = nullptr;
				}
			}
			pChannel++;
		}

	}

	{
		g_ShopServerInfo.ServerID = 116;
		g_ShopServerInfo.LocationID = 0;
		g_ShopServerInfo.ServerIP = IP;
		g_ShopServerInfo.ServerPort = TcpPort;
	}

	{
		g_BorderServerInfo.ServerInfo.ServerID = 200;
		g_BorderServerInfo.ServerInfo.ServerIP = IP;
		g_BorderServerInfo.ServerInfo.TcpPort = TcpPort;
		g_BorderServerInfo.ServerInfo.UdpPort = UdpPort;
		g_BorderServerInfo.ServerInfo.MaxPlayerNum = 10000;
		g_BorderServerInfo.ServerInfo.CurrentPlayerNum = 1;
		g_BorderServerInfo.ServerInfo.RandomKey = 0;
		g_BorderServerInfo.ServerInfo.IsDisabledLogin = 0;
		g_BorderServerInfo.ServerInfo.MultiIPInfo = nullptr;
		g_BorderServerInfo.LocationID = 1;
	}

	{
		g_MatchServerInfo.ServerInfo.ServerID = 300;
		g_MatchServerInfo.ServerInfo.ServerIP = IP;
		g_MatchServerInfo.ServerInfo.TcpPort = TcpPort;
		g_MatchServerInfo.ServerInfo.UdpPort = UdpPort;
		g_MatchServerInfo.ServerInfo.MaxPlayerNum = 10000;
		g_MatchServerInfo.ServerInfo.CurrentPlayerNum = 1;
		g_MatchServerInfo.ServerInfo.RandomKey = 0;
		g_MatchServerInfo.ServerInfo.IsDisabledLogin = 0;
		g_MatchServerInfo.ServerInfo.MultiIPInfo = nullptr;
		g_MatchServerInfo.LocationID = 1;
	}

	{
		g_RelaxServerInfo.ServerInfo.ServerID = 400;
		g_RelaxServerInfo.ServerInfo.ServerIP = IP;
		g_RelaxServerInfo.ServerInfo.TcpPort = TcpPort;
		g_RelaxServerInfo.ServerInfo.UdpPort = UdpPort;
		g_RelaxServerInfo.ServerInfo.MaxPlayerNum = 100;
		g_RelaxServerInfo.ServerInfo.CurrentPlayerNum = 1;
		g_RelaxServerInfo.ServerInfo.RandomKey = 0;
		g_RelaxServerInfo.ServerInfo.IsDisabledLogin = 0;
		g_RelaxServerInfo.ServerInfo.MultiIPInfo = nullptr;
		g_RelaxServerInfo.LocationID = 1;
	}



	{
		g_TeamServerInfo.ServerInfo.ServerID = 700;
		g_TeamServerInfo.ServerInfo.ServerIP = IP;
		g_TeamServerInfo.ServerInfo.TcpPort = TcpPort;
		g_TeamServerInfo.ServerInfo.UdpPort = UdpPort;
		g_TeamServerInfo.ServerInfo.MaxPlayerNum = 10000;
		g_TeamServerInfo.ServerInfo.CurrentPlayerNum = 1;
		g_TeamServerInfo.ServerInfo.RandomKey = 0;
		g_TeamServerInfo.ServerInfo.IsDisabledLogin = 0;
		g_TeamServerInfo.ServerInfo.MultiIPInfo = nullptr;
		g_TeamServerInfo.LocationID = 1;
	}

	{
		g_DanceServerInfo.ServerInfo.ServerID = 800;
		g_DanceServerInfo.ServerInfo.ServerIP = IP;
		g_DanceServerInfo.ServerInfo.TcpPort = TcpPort;
		g_DanceServerInfo.ServerInfo.UdpPort = UdpPort;
		g_DanceServerInfo.ServerInfo.MaxPlayerNum = 10000;
		g_DanceServerInfo.ServerInfo.CurrentPlayerNum = 1;
		g_DanceServerInfo.ServerInfo.RandomKey = 0;
		g_DanceServerInfo.ServerInfo.IsDisabledLogin = 0;
		g_DanceServerInfo.ServerInfo.MultiIPInfo = nullptr;
		g_DanceServerInfo.LocationID = 1;
	}

	{
		g_SlideServerInfo.ServerInfo.ServerID = 900;
		g_SlideServerInfo.ServerInfo.ServerIP = IP;
		g_SlideServerInfo.ServerInfo.TcpPort = TcpPort;
		g_SlideServerInfo.ServerInfo.UdpPort = UdpPort;
		g_SlideServerInfo.ServerInfo.MaxPlayerNum = 10000;
		g_SlideServerInfo.ServerInfo.CurrentPlayerNum = 1;
		g_SlideServerInfo.ServerInfo.RandomKey = 0;
		g_SlideServerInfo.ServerInfo.IsDisabledLogin = 0;
		g_SlideServerInfo.ServerInfo.MultiIPInfo = nullptr;
		g_SlideServerInfo.LocationID = 1;
	}
}

void EventWorld::InitChatRoom()
{
	ChatRooms[0].ID = 0;
	ChatRooms[0].Name = "琳琅湾";

	ChatRooms[0].CurrPlayerNum = 0;
	ChatRooms[0].MaxPlayerNum = 99;
	ChatRooms[0].RoomType = 1;
	ChatRooms[0].SceneID = 109;
	ChatRooms[0].x = 0;
	ChatRooms[0].y = -50000;
	ChatRooms[0].z = 0;
	for (size_t i = 0; i < 99; i++)
	{
		ChatRooms[0].Player[i] = NULL;
	}

	ChatRooms[1].ID = 1;
	ChatRooms[1].Name = "琳琅镇";

	ChatRooms[1].CurrPlayerNum = 0;
	ChatRooms[1].MaxPlayerNum = 99;
	ChatRooms[1].RoomType = 2;
	ChatRooms[1].SceneID = 25;
	ChatRooms[1].x = 0;
	ChatRooms[1].y = 0;
	ChatRooms[1].z = 0;
	for (size_t i = 0; i < 99; i++)
	{
		ChatRooms[1].Player[i] = NULL;
	}

	ChatRooms[2].ID = 2;
	ChatRooms[2].Name = "单身派对";

	ChatRooms[2].CurrPlayerNum = 0;
	ChatRooms[2].MaxPlayerNum = 99;
	ChatRooms[2].RoomType = 3;
	ChatRooms[2].SceneID = 109;
	ChatRooms[2].x = 0;
	ChatRooms[2].y = -40000;
	ChatRooms[2].z = 0;
	for (size_t i = 0; i < 99; i++)
	{
		ChatRooms[2].Player[i] = NULL;
	}

	ChatRooms[3].ID = 3;
	ChatRooms[3].Name = "皇族休闲区";

	ChatRooms[3].CurrPlayerNum = 0;
	ChatRooms[3].MaxPlayerNum = 99;
	ChatRooms[3].RoomType = 4;
	ChatRooms[3].SceneID = 136;
	ChatRooms[3].x = 10000;
	ChatRooms[3].y = 0;
	ChatRooms[3].z = 0;
	for (size_t i = 0; i < 99; i++)
	{
		ChatRooms[3].Player[i] = NULL;
	}

	ChatRooms[4].ID = 4;
	ChatRooms[4].Name = "中国城";

	ChatRooms[4].CurrPlayerNum = 0;
	ChatRooms[4].MaxPlayerNum = 99;
	ChatRooms[4].RoomType = 3;
	ChatRooms[4].SceneID = 4;
	ChatRooms[4].x = 33071;
	ChatRooms[4].y = -45773;
	ChatRooms[4].z = 4368;
	for (size_t i = 0; i < 99; i++)
	{
		ChatRooms[4].Player[i] = NULL;
	}
}
