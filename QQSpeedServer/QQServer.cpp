#include "QQServer.h"

QQServer::QQServer() : TCP(this)
{
}

void QQServer::Run()
{
	if (!TCP->Start("0.0.0.0", 27016))
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		std::cout << "[TCP][QQServer]FAILED" << std::endl;
		return;
	}
}

void QQServer::Send(ClientNode* Client)
{
	BYTE buf[2048]; BYTE* p = buf;
	WORD len;

	Write16(p, 0); //Length

	Write8(p, 2); //STX

	//Version
	Write8(p, 11);
	Write8(p, 0);

	Write16(p, 0x82); //Cmd
	Write16(p, 0); //Seq

	//body
	Write16(p, 0);
	Write16(p, 0);
	Write16(p, 1);

	BYTE MsgHead[260]; BYTE* pMsgHead = MsgHead;
	memset(MsgHead, 0, sizeof(MsgHead));
	Write8(pMsgHead, 0);
	Write8(pMsgHead, 0x28);
	Write8(pMsgHead, 0);

	int outlen = 0;
	BYTE key[16];
	//memset(key, 0, sizeof(key));

	memcpy(key, KEY, 16);


	memcpy(pMsgHead, KEY, 16); //QQKey
	pMsgHead += 16;

	pMsgHead += 28; //???

	Write8(pMsgHead, 1); //SignKeyLength
	memcpy(pMsgHead, "!", 1);
	pMsgHead += 1;


	oi_symmetry_encrypt2(MsgHead, sizeof(MsgHead), key, p, &outlen);
	p += outlen;


	Write8(p, 3); //end

	len = p - buf;
	Set16(buf, len);


	TCP->Send(Client->ConnID, buf, len);
}

void QQServer::OnFullReceive(ClientNode* Client, BYTE* Data, int Length)
{
	Read16(Data); //Length
	Read8(Data); //STX 02开始标志
	Read16(Data); //Version
	short Cmd = Read16(Data);
	Read16(Data); //Seq
	Read32(Data); //uin
	Read16(Data);
	BYTE* key = Data;
	Data += 16;

	int len = Length - 2 - 1 - 2 - 2 - 4 - 2 - 16 - 1;
	BYTE* out = (BYTE*)malloc(len);
	oi_symmetry_decrypt2(Data, len, key, out, &len);

	//Data += len;
	//Read8(Data); //03结束标志
	printf("[QQServer][ConnID:%d]RecvCmd:%d\n", Client->ConnID, Cmd);
	free(out);

	Send(Client);
}

EnHandleResult QQServer::OnPrepareListen(ITcpServer* pSender, SOCKET soListen)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	std::cout << "[TCP][QQServer]SUCCESS" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	return HR_OK;
}

EnHandleResult QQServer::OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient)
{
	printf("[QQServer][ConnID:%lld]OnAccept\n", dwConnID);

	ClientNode* Client = new ClientNode;
	memset(Client, 0, sizeof(ClientNode));
	Client->Server = pSender;
	Client->ConnID = dwConnID;

	pSender->SetConnectionExtra(dwConnID, Client);

	return HR_OK;
}

EnHandleResult QQServer::OnHandShake(ITcpServer* pSender, CONNID dwConnID)
{
	return HR_IGNORE;
}

EnHandleResult QQServer::OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	ClientNode* Client;
	pSender->GetConnectionExtra(dwConnID, (PVOID*)&Client);

	if (iLength < sizeof(int))
	{
		return HR_ERROR;
	}

	long left;
	long need;
	const int MaxBuf = 8192;
	void* p;
	do
	{
		if (Client->BufferPtr)
		{
			if (Client->BufferOffset < sizeof(short))
			{
				left = min(iLength, int(sizeof(short) - Client->BufferOffset));
				memcpy((void*)(Client->BufferPtr + Client->BufferOffset), pData, left);
				Client->BufferOffset += left;
				if (Client->BufferOffset < sizeof(short))
				{
					break;
				}
				pData += left;
				iLength -= left;
			}
			need = ntohs(*(u_short*)Client->BufferPtr);
			left = need - Client->BufferOffset;
			if (need > Client->BufferSize)
			{
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
		}
		while (iLength > 0)
		{
			if (iLength < sizeof(short))
			{
				need = sizeof(short);
			}
			else
			{
				need = ntohs(*(u_short*)pData);
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

EnHandleResult QQServer::OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	return HR_OK;
}

EnHandleResult QQServer::OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
	ClientNode* Client;
	pSender->GetConnectionExtra(dwConnID, (PVOID*)&Client);
	printf("[QQServer][ConnID:%lld]OnClose\n", dwConnID);

	if (Client->BufferPtr)
	{
		free((PVOID)Client->BufferPtr);
	}
	delete Client;

	return HR_OK;
}

EnHandleResult QQServer::OnShutdown(ITcpServer* pSender)
{
	printf("[QQServer]Close\n");

	return HR_OK;
}
