#include "EventWorldInfo.h"

EventWorldInfo::EventWorldInfo() {}

EventWorldInfo::EventWorldInfo(CacheUser* cacheUser, CachePlayer* cachePlayer) : pCacheUser(cacheUser), pCachePlayer(cachePlayer) {}

EventWorldInfo::~EventWorldInfo() {}

void EventWorldInfo::Notify(ClientNode* Client) {}

void EventWorldInfo::Response(ClientNode* Client) {}

void EventWorldInfo::Response(ClientNode* Client, UINT ClientVersion, UINT MasterVersion, UINT Slaveversion)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;


	USHORT ResultID = 0;
	const char* Reason = "";
	if (!Client->IsLogin)
	{
		ResultID = 1;
		Reason = "the password is incorrect";
	}

	Write16(p, ResultID);
	Write32(p, ClientVersion); //LastClientVersion
	Write32(p, MasterVersion); //LastMasterVersion
	Write32(p, 4); //LastSlaveVersion

	Write8(p, 0); //OldDownloadServerNum

	const char RootDirection[] = "qqkart/test";
	len = strlen(RootDirection);
	Write8(p, (BYTE)len); //RootDirectionLen
	memcpy(p, RootDirection, len);
	p += len;

	Write32(p, 25); //MasterFullVersion
	Write32(p, 0); //SlaveFullVersion
	Write16(p, 0); //P2POption

	Write8(p, 1); //WorldCount
	{ //WorldBaseInfo
		BYTE* pWorldBaseInfo = p;
		Write16(pWorldBaseInfo, 0); //len


		Write8(pWorldBaseInfo, g_WorldBaseInfo.WorldID);

		len = strlen(g_WorldBaseInfo.Name);
		Write8(pWorldBaseInfo, (BYTE)len);
		memcpy(pWorldBaseInfo, g_WorldBaseInfo.Name, len);
		pWorldBaseInfo += len;


		Write8(pWorldBaseInfo, g_WorldBaseInfo.DirNum);
		DirServerInfo* pDir = g_WorldBaseInfo.Dir;
		for (size_t i = 0; i < g_WorldBaseInfo.DirNum; i++)
		{ //DirServerInfo
			BYTE* pDirServerInfo = pWorldBaseInfo;
			Write16(pDirServerInfo, 0); //len


			Write32(pDirServerInfo, pDir->ServerID);
			Write16(pDirServerInfo, pDir->LocationID);
			Write32(pDirServerInfo, pDir->ServerIP);
			for (size_t i = 0; i < MAX_DIR_LISTEN_PORT_NUM; i++)
			{
				Write16(pDirServerInfo, pDir->ServerPort[i]);
			}

			Write8(pDirServerInfo, pDir->MultiIPInfo ? 1 : 0); //HasMultiIPInfo

			pDir++;

			len = pDirServerInfo - pWorldBaseInfo;
			Set16(pWorldBaseInfo, (WORD)len);
			pWorldBaseInfo += len;
		}

		len = pWorldBaseInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	if (Client->IsLogin)
	{
		Write8(p, 1); //CountryCount
		{ //CountryInfo
			BYTE* pCountryInfo = p;
			Write16(pCountryInfo, 0); //len

			Write8(pCountryInfo, g_CountryInfo.CountryID);
			Write8(pCountryInfo, g_CountryInfo.ChannelNum);
			ChannelInfo* pChannel = g_CountryInfo.Channel;
			for (size_t i = 0; i < g_CountryInfo.ChannelNum; i++)
			{
				BYTE* pChannelInfo = pCountryInfo;
				Write16(pChannelInfo, 0); //len

				Write8(pChannelInfo, pChannel->ChannelID);
				Write8(pChannelInfo, pChannel->IDCNum);
				IDCServerInfo* pIDC = pChannel->IDC;
				for (size_t i = 0; i < pChannel->IDCNum; i++)
				{
					BYTE* pIDCServerInfo = pChannelInfo;
					Write16(pIDCServerInfo, 0); //len

					Write16(pIDCServerInfo, pIDC->LocationID);
					Write8(pIDCServerInfo, pIDC->GameServerNum);
					GameServerInfo* pGameServer = pIDC->GameServer;
					for (size_t i = 0; i < pIDC->GameServerNum; i++)
					{
						BYTE* pGameServerInfo = pIDCServerInfo;
						Write16(pGameServerInfo, 0); //len


						Write32(pGameServerInfo, pGameServer->ServerID);
						Write32(pGameServerInfo, pGameServer->ServerIP);
						Write16(pGameServerInfo, pGameServer->TcpPort);
						Write16(pGameServerInfo, pGameServer->UdpPort);
						Write16(pGameServerInfo, pGameServer->MaxPlayerNum);
						Write16(pGameServerInfo, pGameServer->CurrentPlayerNum);
						Write32(pGameServerInfo, pGameServer->RandomKey);

						Write8(pGameServerInfo, pGameServer->IsDisabledLogin);
						Write8(pGameServerInfo, pGameServer->MultiIPInfo ? 1 : 0); //HasMultiIPInfo

						pGameServer++;

						len = pGameServerInfo - pIDCServerInfo;
						Set16(pIDCServerInfo, (WORD)len);
						pIDCServerInfo += len;
					}

					pIDC++;

					len = pIDCServerInfo - pChannelInfo;
					Set16(pChannelInfo, (WORD)len);
					pChannelInfo += len;
				}

				pChannel++;

				len = pChannelInfo - pCountryInfo;
				Set16(pCountryInfo, (WORD)len);
				pCountryInfo += len;
			}

			len = pCountryInfo - p;
			Set16(p, (WORD)len);
			p += len;
		}
	}
	else
	{
		Write8(p, 0); //CountryCount
	}

	Write8(p, 1); //ShopServerCount
	{ //ShopServerInfo
		BYTE* pShopServerInfo = p;
		Write16(pShopServerInfo, 0); //len

		Write32(pShopServerInfo, g_ShopServerInfo.ServerID);
		Write16(pShopServerInfo, g_ShopServerInfo.LocationID);
		Write32(pShopServerInfo, g_ShopServerInfo.ServerIP);
		Write16(pShopServerInfo, g_ShopServerInfo.ServerPort);

		len = pShopServerInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write8(p, 1); //BorderServerCount
	{ //BorderServerInfo
		BYTE* pBorderServerInfo = p;
		Write16(pBorderServerInfo, 0); //len

		{
			BYTE* pServerInfo = pBorderServerInfo;
			Write16(pServerInfo, 0); //len

			Write32(pServerInfo, g_BorderServerInfo.ServerInfo.ServerID);
			Write32(pServerInfo, g_BorderServerInfo.ServerInfo.ServerIP);
			Write16(pServerInfo, g_BorderServerInfo.ServerInfo.TcpPort);
			Write16(pServerInfo, g_BorderServerInfo.ServerInfo.UdpPort);
			Write16(pServerInfo, g_BorderServerInfo.ServerInfo.MaxPlayerNum);
			Write16(pServerInfo, g_BorderServerInfo.ServerInfo.CurrentPlayerNum);
			Write32(pServerInfo, g_BorderServerInfo.ServerInfo.RandomKey);

			Write8(pServerInfo, g_BorderServerInfo.ServerInfo.IsDisabledLogin);
			Write8(pServerInfo, g_BorderServerInfo.ServerInfo.MultiIPInfo ? 1 : 0); //HasMultiIPInfo

			len = pServerInfo - pBorderServerInfo;
			Set16(pBorderServerInfo, (WORD)len);
			pBorderServerInfo += len;
		}
		Write16(pBorderServerInfo, g_BorderServerInfo.LocationID);

		len = pBorderServerInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write8(p, 1); //MatchServerCount
	{ //MatchServerInfo
		BYTE* pMatchServerInfo = p;
		Write16(pMatchServerInfo, 0); //len

		{
			BYTE* pServerInfo = pMatchServerInfo;
			Write16(pServerInfo, 0); //len

			Write32(pServerInfo, g_MatchServerInfo.ServerInfo.ServerID);
			Write32(pServerInfo, g_MatchServerInfo.ServerInfo.ServerIP);
			Write16(pServerInfo, g_MatchServerInfo.ServerInfo.TcpPort);
			Write16(pServerInfo, g_MatchServerInfo.ServerInfo.UdpPort);
			Write16(pServerInfo, g_MatchServerInfo.ServerInfo.MaxPlayerNum);
			Write16(pServerInfo, g_MatchServerInfo.ServerInfo.CurrentPlayerNum);
			Write32(pServerInfo, g_MatchServerInfo.ServerInfo.RandomKey);

			Write8(pServerInfo, g_MatchServerInfo.ServerInfo.IsDisabledLogin);
			Write8(pServerInfo, g_MatchServerInfo.ServerInfo.MultiIPInfo ? 1 : 0); //HasMultiIPInfo

			len = pServerInfo - pMatchServerInfo;
			Set16(pMatchServerInfo, (WORD)len);
			pMatchServerInfo += len;
		}
		Write16(pMatchServerInfo, g_MatchServerInfo.LocationID);

		len = pMatchServerInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write8(p, 1); //RelaxServerCount
	{ //RelaxServerInfo
		BYTE* pRelaxServerInfo = p;
		Write16(pRelaxServerInfo, 0); //len

		{
			BYTE* pServerInfo = pRelaxServerInfo;
			Write16(pServerInfo, 0); //len

			Write32(pServerInfo, g_RelaxServerInfo.ServerInfo.ServerID);
			Write32(pServerInfo, g_RelaxServerInfo.ServerInfo.ServerIP);
			Write16(pServerInfo, g_RelaxServerInfo.ServerInfo.TcpPort);
			Write16(pServerInfo, g_RelaxServerInfo.ServerInfo.UdpPort);
			Write16(pServerInfo, g_RelaxServerInfo.ServerInfo.MaxPlayerNum);
			Write16(pServerInfo, g_RelaxServerInfo.ServerInfo.CurrentPlayerNum);
			Write32(pServerInfo, g_RelaxServerInfo.ServerInfo.RandomKey);

			Write8(pServerInfo, g_RelaxServerInfo.ServerInfo.IsDisabledLogin);
			Write8(pServerInfo, g_RelaxServerInfo.ServerInfo.MultiIPInfo ? 1 : 0); //HasMultiIPInfo

			len = pServerInfo - pRelaxServerInfo;
			Set16(pRelaxServerInfo, (WORD)len);
			pRelaxServerInfo += len;
		}
		Write16(pRelaxServerInfo, g_RelaxServerInfo.LocationID);

		len = pRelaxServerInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write8(p, 0); //NetAdminServerCount


	len = strlen(Reason);
	Write16(p, (WORD)len); //ReasonLen
	memcpy(p, Reason, len);
	p += len;

	Write8(p, 0); //DownloadServerNum


	Write8(p, 1); //TeamServerCount
	{ //TeamServerInfo
		BYTE* pTeamServerInfo = p;
		Write16(pTeamServerInfo, 0); //len

		{
			BYTE* pServerInfo = pTeamServerInfo;
			Write16(pServerInfo, 0); //len

			Write32(pServerInfo, g_TeamServerInfo.ServerInfo.ServerID);
			Write32(pServerInfo, g_TeamServerInfo.ServerInfo.ServerIP);
			Write16(pServerInfo, g_TeamServerInfo.ServerInfo.TcpPort);
			Write16(pServerInfo, g_TeamServerInfo.ServerInfo.UdpPort);
			Write16(pServerInfo, g_TeamServerInfo.ServerInfo.MaxPlayerNum);
			Write16(pServerInfo, g_TeamServerInfo.ServerInfo.CurrentPlayerNum);
			Write32(pServerInfo, g_TeamServerInfo.ServerInfo.RandomKey);

			Write8(pServerInfo, g_TeamServerInfo.ServerInfo.IsDisabledLogin);
			Write8(pServerInfo, g_TeamServerInfo.ServerInfo.MultiIPInfo ? 1 : 0); //HasMultiIPInfo

			len = pServerInfo - pTeamServerInfo;
			Set16(pTeamServerInfo, (WORD)len);
			pTeamServerInfo += len;
		}
		Write16(pTeamServerInfo, g_TeamServerInfo.LocationID);

		len = pTeamServerInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write8(p, 1); //DanceServerCount
	{ //DanceServerInfo
		BYTE* pDanceServerInfo = p;
		Write16(pDanceServerInfo, 0); //len

		{
			BYTE* pServerInfo = pDanceServerInfo;
			Write16(pServerInfo, 0); //len

			Write32(pServerInfo, g_DanceServerInfo.ServerInfo.ServerID);
			Write32(pServerInfo, g_DanceServerInfo.ServerInfo.ServerIP);
			Write16(pServerInfo, g_DanceServerInfo.ServerInfo.TcpPort);
			Write16(pServerInfo, g_DanceServerInfo.ServerInfo.UdpPort);
			Write16(pServerInfo, g_DanceServerInfo.ServerInfo.MaxPlayerNum);
			Write16(pServerInfo, g_DanceServerInfo.ServerInfo.CurrentPlayerNum);
			Write32(pServerInfo, g_DanceServerInfo.ServerInfo.RandomKey);

			Write8(pServerInfo, g_DanceServerInfo.ServerInfo.IsDisabledLogin);
			Write8(pServerInfo, g_DanceServerInfo.ServerInfo.MultiIPInfo ? 1 : 0); //HasMultiIPInfo

			len = pServerInfo - pDanceServerInfo;
			Set16(pDanceServerInfo, (WORD)len);
			pDanceServerInfo += len;
		}
		Write16(pDanceServerInfo, g_DanceServerInfo.LocationID);

		len = pDanceServerInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write8(p, 1); //SlideServerCount
	{ //SlideServerInfo
		BYTE* pSlideServerInfo = p;
		Write16(pSlideServerInfo, 0); //len

		{
			BYTE* pServerInfo = pSlideServerInfo;
			Write16(pServerInfo, 0); //len

			Write32(pServerInfo, g_SlideServerInfo.ServerInfo.ServerID);
			Write32(pServerInfo, g_SlideServerInfo.ServerInfo.ServerIP);
			Write16(pServerInfo, g_SlideServerInfo.ServerInfo.TcpPort);
			Write16(pServerInfo, g_SlideServerInfo.ServerInfo.UdpPort);
			Write16(pServerInfo, g_SlideServerInfo.ServerInfo.MaxPlayerNum);
			Write16(pServerInfo, g_SlideServerInfo.ServerInfo.CurrentPlayerNum);
			Write32(pServerInfo, g_SlideServerInfo.ServerInfo.RandomKey);

			Write8(pServerInfo, g_SlideServerInfo.ServerInfo.IsDisabledLogin);
			Write8(pServerInfo, g_SlideServerInfo.ServerInfo.MultiIPInfo ? 1 : 0); //HasMultiIPInfo

			len = pServerInfo - pSlideServerInfo;
			Set16(pSlideServerInfo, (WORD)len);
			pSlideServerInfo += len;
		}
		Write16(pSlideServerInfo, g_SlideServerInfo.LocationID);

		len = pSlideServerInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write32(p, 0); //UpdateType
	Write8(p, 0); //OpenOtherIDCFlag
	Write16(p, 0); //OtherIDCID

	Write8(p, 0); //BugReportServerCount

	Write8(p, 0); //IsDynamicDownloadPermitted
	Write8(p, 0); //DynamicDownloadResourceIdNum
	//DynamicDownloadResourceIds[]

	Write8(p, 0); //EnableRandMapMusicPreKnown

	Write16(p, 0); //MinPlayerNumForRand
	Write16(p, 0); //PlayerNumDeltaForRand

	Write8(p, 0); //FBServerCount

	const char WebCGIDomain[] = "localhost";
	len = strlen(WebCGIDomain);
	Write8(p, (BYTE)len); //WebCGIDomainLen
	memcpy(p, WebCGIDomain, len);
	p += len;

	Write16(p, 8000); //WebCGIServerPort

	Write8(p, 0); //WlMatchSvrCount
	Write8(p, 0); //SkateServerCount


	Write8(p, 0); //VersionCount
	//VersionList[]

	Write32(p, 0); //IsEnableBETA
	Write32(p, 0); //AreaID

	Write8(p, 0); //PreVersionCount
	//PreVersionList[]

	Write8(p, 0); //IsEnableMapTester
	Write8(p, 0); //DisableRandomDanceSvr
	Write8(p, 0); //DisableRandomSkateSvr


	//m_abyClientSwitch[16]
	memset(p, 0, 16);
	p += 16;

	Write16(p, 0); //PreResoveDomainNum

	Write8(p, 0); //MRServerCount


	Write16(p, 0); //MinPlayerNumForRandForGsvrd6

	Write8(p, 0); //NpcServerCount


	Write8(p, 0); //PatchCount

	Write8(p, 0); //UrlCount

	Write16(p, 0); //LoginBuffLen

	Write16(p, 0); //WebURLLen


	len = p - buf;
	SendToClient(Client, 90, buf, len, 0, FE_DIRSVRD, 0, MsgType::Response);
}

void EventWorldInfo::Request(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	UINT ClientVersion = Read32(Body);
	UINT MasterVersion = Read32(Body);
	UINT SlaveVersion = Read32(Body);
	BYTE WorldID = Read8(Body);

	//BYTE FileHash[32];
	Body += 32;

	BYTE ClientCnt = Read8(Body);
	BYTE IsSimplifyVersion = Read8(Body);

	UINT PlayerFlag = Read32(Body);

	BYTE FileNum = Read8(Body);
	//UINT ClientFileCRC[FileNum];
	Body += FileNum * sizeof(UINT);

	//printf("[RequestGetWorldInfo]ClientVersion:%d, MasterVersion:%d, SlaveVersion:%d\n", ClientVersion, MasterVersion, SlaveVersion);

	Response(Client, ClientVersion, MasterVersion, SlaveVersion);

	//Client->Server->Disconnect(Client->ConnID);
}
