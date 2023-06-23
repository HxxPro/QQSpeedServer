#include "GameServer.h"

GameServer::GameServer() : TCP(this), UDP(this)
{
	RegisterEvent();
}

GameServer::GameServer(CacheUser* u, CachePlayer* p) : TCP(this), UDP(this)
{
	pCacheUser = u;
	pCachePlayer = p;
	RegisterEvent();
}

GameServer::~GameServer()
{
}

void GameServer::RegisterEvent()
{
	eventHandlers[1] = std::make_shared<UserEventHandler>();
	eventHandlers[2] = std::make_shared<UserEventHandler>();
	eventHandlers[90] = std::make_shared<WorldEventHandler>();
	eventHandlers[91] = std::make_shared<WorldEventHandler>();
	eventHandlers[100] = std::make_shared<PlayerEventHandler>();
	eventHandlers[101] = std::make_shared<PlayerEventHandler>();
}

void GameServer::Run()
{
	if (!TCP->Start("0.0.0.0", 27015))
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		std::cout << "[TCP][GameServer]FAILED" << std::endl;
		return;
	}

	UDP->Start("0.0.0.0", 27015, CM_UNICAST, nullptr);

	char ch[4096];
	do
	{
		fputs(">", stdout);
		fgets(ch, 4096, stdin);

		if (_stricmp(ch, "cls\n") == 0)
		{
			system("cls");
		}
		else if (_stricmp(ch, "test\n") == 0)
		{
			std::cout << "There are currently no projects to test." << std::endl;
		}
	} while (_stricmp(ch, "exit\n") != 0);
	fputs("Bye\n", stdout);

	UDP->Stop();
	TCP->Stop();
}

void GameServer::OnFullReceive(ClientNode* Client, BYTE* Data, size_t Length)
{
	if (Length < sizeof(CSHEAD))
	{
		Client->Server->Disconnect(Client->ConnID);
		return;
	}

	CSHEAD* ProtocolHead = (CSHEAD*)Data;
	BYTE* Body;
	DWORD HeadLen = sizeof(CSHEAD) + ProtocolHead->OptLength;

	if (Length < HeadLen)
	{
		Client->Server->Disconnect(Client->ConnID);
		return;
	}

	if (ProtocolHead->OptLength)
	{
		Body = (BYTE*)(ProtocolHead + 1);
		//官方服务器应该根据这个进行查表获取key
		//而我们偷懒,把它作为登录密码,这样其实不安全,并且它是明文传输的

		char* Password = new char[ProtocolHead->OptLength + 1];
		memcpy(Password, Body, ProtocolHead->OptLength);
		Password[ProtocolHead->OptLength] = 0;

		//这里应该修改为从缓存中读取
		/*
		mMySQL msql;
		//这里是导致由于身份限制,你无法进行登录的原因.
		if (msql.MMYSQL_CmpPassword(ntohl(ProtocolHead->Uin), Password))
		{
			Client->IsLogin = TRUE;
		}
		delete[] Password;
		*/


	}

	DWORD BodyLen = Length - HeadLen;
	if (BodyLen >= sizeof(MSGHEAD))//0x000001D1D93FC5B0
	{
		//这里不使用__int64会导致丢失数据
		MSGHEAD* MsgHead = (MSGHEAD*)((__int64)Data + HeadLen);
		if (ProtocolHead->BodyFlag)
		{
			Body = (BYTE*)malloc(BodyLen);
			if (!Body)
			{
				return;
			}
			if (oi_symmetry_decrypt2((BYTE*)MsgHead, BodyLen, Client->Key, Body, (int*)&BodyLen) == false)
			{
				printf("[ConnID:%d]Decryption failed!\n", Client->ConnID);
				free(Body);
				return;
			}
		}
		else
		{
			Body = (BYTE*)malloc(BodyLen);
			if (!Body)
			{
				return;
			}
			memcpy(Body, MsgHead, BodyLen);
		}
		MsgHead = (MSGHEAD*)Body;
		Body = (BYTE*)Body + sizeof(MSGHEAD);
		BodyLen = BodyLen - sizeof(MSGHEAD);

		if (ProtocolHead->OptLength)
		{
			Client->ServerID = ntohs(MsgHead->DstID);
		}
		OnRecvFromClient(Client, ntohs(MsgHead->MsgID), Body, ntohs(MsgHead->BodyLen));

		free(MsgHead);
	}
	else
	{
		printf("[ConnID:%d]Request to check for updates is not supported\n", Client->ConnID);
		Client->Server->Disconnect(Client->ConnID);
	}
}

void GameServer::OnRecvFromClient(ClientNode* Client, USHORT MsgID, BYTE* Body, size_t BodyLen)
{
	if (!Client->IsLogin && MsgID > 100)
	{
		printf("[GameServer][ConnID:%d]RecvMsg:%d - Unlawful packets for users who are not logged in\n", Client->ConnID, MsgID);
		return;
	}

	auto it = eventHandlers.find(MsgID);
	if (it != eventHandlers.end())
	{
		Message message(MsgID, Body, BodyLen, pCacheUser, pCachePlayer);
		it->second->HandleMessage(Client, message);
	}
	else
	{
		printf("[GameServer][ConnID:%d]RecvMsg:%d - Unregistered message\n", Client->ConnID, MsgID);
	}
}

unsigned short GameServer::CheckSum(const BYTE* pBuffer, int nBufLen)
{
	if (NULL == pBuffer || nBufLen < 1)
	{
		return 0;
	}

	unsigned long nSum = 0;
	unsigned short* pData = (unsigned short*)pBuffer;

	int nLen = nBufLen / 2;
	int nMod = nBufLen % 2;

	for (int i = 0; i < nLen; i++)
	{
		nSum += pData[i];
	}

	unsigned short nShort = 0;

	if (1 == nMod)
	{
		nShort = (unsigned short)pBuffer[nBufLen - 1];
		nSum += nShort;
	}
	nSum = (nSum >> 16) + (nSum & 0xffff);
	nSum += (nSum >> 16);
	nShort = ~((unsigned short)nSum);

	return nShort;
}

void GameServer::SendUdpData(LPCTSTR lpszRemoteAddress, USHORT usRemotePort, short Cmd, const BYTE* Data, int Len, ULONG Seq, SHORT DialogID, ULONG Uin)
{
	int BufferLength = sizeof(TransferHead) + Len;
	BYTE* Buffer = (BYTE*)malloc(BufferLength);
	if (!Buffer)
	{
		return;
	}
	TransferHead* ProtocolHead = (TransferHead*)Buffer;
	ProtocolHead->TotalLength = htons(BufferLength);
	ProtocolHead->Ver = 0;
	ProtocolHead->Seq = htonl(Seq);
	ProtocolHead->DialogID = htons(DialogID);
	ProtocolHead->Uin = htonl(Uin);
	ProtocolHead->TransferCmd = htons(Cmd);
	ProtocolHead->CheckSum = 0;
	ProtocolHead->OptLength = (UCHAR)Len;

	memcpy(ProtocolHead + 1, Data, Len);

	ProtocolHead->CheckSum = htons(CheckSum(Buffer, BufferLength));

	UDP->Send(lpszRemoteAddress, usRemotePort, Buffer, BufferLength);
	free(Buffer);

	printf("[UDP:Send]Cmd:%d\n", Cmd);
}

EnHandleResult GameServer::OnPrepareListen(ITcpServer* pSender, SOCKET soListen)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	std::cout << "[TCP][GameServer]SUCCESS" << std::endl;

	return HR_OK;
}

EnHandleResult GameServer::OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient)
{
	printf("[GameServer][ConnID:%lld]OnAccept\n", dwConnID);

	ClientNode* Client = new ClientNode;
	memset(Client, 0, sizeof(ClientNode));
	Client->Server = pSender;
	Client->ConnID = dwConnID;
	memcpy(Client->Key, KEY, 16);
	Client->KartID = 10020;

	pSender->SetConnectionExtra(dwConnID, Client);

	return HR_OK;
}

EnHandleResult GameServer::OnHandShake(ITcpServer* pSender, CONNID dwConnID)
{
	printf("[GameServer][ConnID:%lld]OnHandShake\n", dwConnID);
	return HR_IGNORE;
}

EnHandleResult GameServer::OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	ClientNode* Client;
	pSender->GetConnectionExtra(dwConnID, (PVOID*)&Client);

	//printf("[GameServer][ConnID:%d]OnReceive\n", dwConnID);

	if (iLength < sizeof(int))
	{
		return HR_ERROR;
	}

	long left;
	long need;
	const int MaxBuf = MAXWORD;
	void* p;
	do
	{
		if (Client->BufferPtr)
		{
			if (Client->BufferOffset < sizeof(int))
			{
				left = min(iLength, int(sizeof(int) - Client->BufferOffset));
				memcpy((void*)(Client->BufferPtr + Client->BufferOffset), pData, left);
				Client->BufferOffset += left;
				if (Client->BufferOffset < sizeof(int))
				{
					break;
				}
				pData += left;
				iLength -= left;
			}
			need = ntohl(*(u_long*)Client->BufferPtr);
			left = need - Client->BufferOffset;
			if (need > Client->BufferSize)
			{
				if (need > 65535) //If the data packet sent by the client is too large, it will not be processed.
				{
					Client->Server->Disconnect(Client->ConnID);
					break;
				}
				if (left > MaxBuf)
				{
					left = max(iLength, MaxBuf);
					Client->BufferSize = Client->BufferOffset + left;
				}
				else
				{
					Client->BufferSize = need;
				}
				p = realloc((void*)Client->BufferPtr, Client->BufferSize);
				if (!p)
				{
					printf("内存不足\n");
					TCP->Stop();
					break;
				}
				Client->BufferPtr = (ULONG_PTR)p;
			}
			if (left >= 0)
			{
				left = min(iLength, left);
				memcpy((void*)(Client->BufferPtr + Client->BufferOffset), pData, left);
				Client->BufferOffset += left;
				if (Client->BufferOffset < need)
				{
					break;
				}
				OnFullReceive(Client, (BYTE*)Client->BufferPtr, need);
				pData += left;
				iLength -= left;
			}
			free((void*)Client->BufferPtr);
			Client->BufferPtr = 0;
			Client->BufferOffset = 0;

			if (Client->BufferOffset == need)
			{
				OnFullReceive(Client, (BYTE*)Client->BufferPtr, need);

				free((void*)Client->BufferPtr);
				Client->BufferPtr = 0;
				Client->BufferOffset = 0;
			}
		}
		while (iLength > 0)
		{
			const u_long* ptr = reinterpret_cast<const u_long*>(pData);

			if (iLength < ntohl(*ptr))
			{
				break;
			}
			if (iLength < sizeof(int))
			{
				need = sizeof(int);
			}
			else
			{
				need = ntohl(*ptr);
			}
			if (need > iLength)
			{
				if (need > MaxBuf)
				{
					Client->BufferSize = max(iLength, MaxBuf);
				}
				else
				{
					Client->BufferSize = need;
				}
				p = malloc(Client->BufferSize);
				if (!p)
				{
					printf("内存不足\n");
					TCP->Stop();
					break;
				}
				Client->BufferPtr = (ULONG_PTR)p;
				memcpy((void*)Client->BufferPtr, pData, iLength);
				Client->BufferOffset = iLength;
				break;
			}
			else
			{
				OnFullReceive(Client, (BYTE*)pData, need);
				pData += need;
				iLength -= need;
			}
		}
	} while (false);
	return HR_OK;
}

EnHandleResult GameServer::OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	return HR_OK;
}

EnHandleResult GameServer::OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
	ClientNode* Client;
	pSender->GetConnectionExtra(dwConnID, (PVOID*)&Client);
	printf("[GameServer][ConnID:%lld]OnClose\n", dwConnID);
	/*
	pEventRoom->LeaveRoom(Client, 0);
	pEventOutdoor->LeaveOutdoor(Client);
	*/
	if (Client->BufferPtr)
	{
		free((PVOID)Client->BufferPtr);
	}
	delete Client;

	return HR_OK;
}

EnHandleResult GameServer::OnShutdown(ITcpServer* pSender)
{
	printf("[GameServer]Close\n");
	return HR_OK;
}

EnHandleResult GameServer::OnPrepareListen(IUdpNode* pSender, SOCKET soListen)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	std::cout << "[UDP][GameServer]SUCCESS" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	return HR_OK;
}

EnHandleResult GameServer::OnSend(IUdpNode* pSender, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength)
{
	return HR_OK;
}

EnHandleResult GameServer::OnReceive(IUdpNode* pSender, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength)
{
	TransferHead* ProtocolHead = (TransferHead*)pData;

	if (iLength < sizeof(TransferHead) && ntohs(ProtocolHead->TotalLength) > iLength)
		return HR_OK;

	UINT Seq = ntohl(ProtocolHead->Seq);
	short DialogID = ntohs(ProtocolHead->DialogID);
	UINT Uin = ntohl(ProtocolHead->Uin);
	short TransferCmd = ntohs(ProtocolHead->TransferCmd);
	UCHAR OptLength = ProtocolHead->OptLength;

	printf("[UDP:OnReceive]Uin:%d, TransferCmd:%d, OptLength:%d\n", Uin, TransferCmd, OptLength);

	size_t len = 0;
	BYTE* p = PBYTE(ProtocolHead + 1);
	UCHAR option[127];

	switch (TransferCmd)
	{
	case UDP_CMD_LOGIN_SERVER:
	{
		in_addr LocalIP;
		LocalIP.S_un.S_addr = Read32(p);
		USHORT LocalPort = Read16(p);

		printf("LocalIP:%s, LocalPort:%d\n", inet_ntoa(LocalIP), LocalPort);

		p = option;

		Write32(p, inet_addr(lpszRemoteAddress));

		len = p - option;
		//SendUdpData(lpszRemoteAddress, usRemotePort, UDP_CMD_LOGIN_SERVER, option, len, Seq, DialogID, Uin);
		break;
	}
	case UDP_CMD_P2P_GAME_DATA:
	{
		//while (OptLength > 0)
		//{
		//	short PlayerID = Read16(p);
		//	UINT PlayerUin = Read32(p);
		//	UINT Time = Read32(p);
		//	printf("PlayerID:%d, PlayerUin:%d, Time:%d\n", PlayerID, PlayerUin, Time);
		//	OptLength -= 10;
		//}
		break;
	}
	case UDP_CMD_SHOW_MY_IP_PORT:
	{
		short SrcPlayerID = Read16(p); //src player id
		UINT SrcUin = Read32(p); //src player uin
		in_addr LocalIP;
		LocalIP.S_un.S_addr = Read32(p);
		USHORT LocalPort = Read16(p);

		printf("SrcPlayerID:%d, SrcUin:%d\n", SrcPlayerID, SrcUin);

		p = option;
		Write16(p, SrcPlayerID); //SrcPlayerID
		Write32(p, SrcUin); //SrcUin
		Write32(p, LocalIP.S_un.S_addr); //SrcOuterIP
		Write16(p, LocalPort); //SrcOuterPort
		Write32(p, inet_addr(lpszRemoteAddress)); //SrcInerIP
		Write16(p, usRemotePort); //SrcInnerPort

		len = p - option;
		//SendUdpData(lpszRemoteAddress, usRemotePort, UDP_CMD_RECV_OTHER_IP_PORT, option, len, Seq, DialogID, Uin);
		break;
	}
	case UDP_CMD_HEART_BEAT:
	{
		p = option;

		len = p - option;
		SendUdpData(lpszRemoteAddress, usRemotePort, UDP_CMD_HEART_BEAT, option, len, Seq, DialogID, Uin);
		break;
	}
	default:
		break;
	}

	return HR_OK;
}

EnHandleResult GameServer::OnShutdown(IUdpNode* pSender)
{
	return HR_OK;
}

EnHandleResult GameServer::OnError(IUdpNode* pSender, EnSocketOperation enOperation, int iErrorCode, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pBuffer, int iLength)
{
	return HR_OK;
}
