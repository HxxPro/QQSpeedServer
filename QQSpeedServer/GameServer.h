#pragma once
#include "stdafx.h"
#include "EventHandler.h"

#include "CacheUser.h"
#include "CachePlayer.h"


enum UdpCmd {
	//udp cs cmds
	UDP_CMD_LOGIN_SERVER = 0x01,
	UDP_CMD_P2P_GAME_DATA = 0x02,
	UDP_CMD_SHOW_MY_IP_PORT = 0x03,
	UDP_CMD_RECV_OTHER_IP_PORT = 0x04,
	UDP_CMD_HEART_BEAT = 0x05,

	//udp cc cmds
	UDP_CMD_TEST_CONNECTION_NO_RECEIVE = 0x20,
	UDP_CMD_TEST_CONNECTION_RECEIVED = 0x21,
	UDP_CMD_UDP_BIDIRECTIONAL_OK = 0x22,
	UDP_CMD_CLIENT_HELLO = 0x25,
	UDP_CMD_CLIENT_P2P_DATA = 0x26,

	UDP_CMD_TEST_NETSPEED = 0x27,
	UDP_CMD_TEST_NETSPEED_REPLY = 0x28
};

class GameServer : public CTcpServerListener, public CUdpNodeListener
{
private:
	CTcpServerPtr TCP;
	CUdpNodePtr UDP;

	CacheUser* pCacheUser = nullptr;
	CachePlayer* pCachePlayer = nullptr;

public:
	GameServer();
	GameServer(CacheUser* u, CachePlayer* p);
	~GameServer();

	void RegisterEvent();

	void Run();

private:
	std::unordered_map<USHORT, std::shared_ptr<EventHandler>> eventHandlers;

	void OnFullReceive(ClientNode* Client, BYTE* Data, size_t Length);
	void OnRecvFromClient(ClientNode* Client, USHORT MsgID, BYTE* Body, size_t BodyLen);

	unsigned short CheckSum(const BYTE* pBuffer, int nBufLen);
	void SendUdpData(LPCTSTR lpszRemoteAddress, USHORT usRemotePort, short Cmd, const BYTE* Data, int Len, ULONG Seq, SHORT DialogID, ULONG Uin);

	virtual EnHandleResult OnPrepareListen(ITcpServer* pSender, SOCKET soListen);
	virtual EnHandleResult OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient);
	virtual EnHandleResult OnHandShake(ITcpServer* pSender, CONNID dwConnID);
	virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);
	virtual EnHandleResult OnShutdown(ITcpServer* pSender);

	virtual EnHandleResult OnPrepareListen(IUdpNode* pSender, SOCKET soListen);
	virtual EnHandleResult OnSend(IUdpNode* pSender, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength);
	virtual EnHandleResult OnReceive(IUdpNode* pSender, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength);
	virtual EnHandleResult OnShutdown(IUdpNode* pSender);
	virtual EnHandleResult OnError(IUdpNode* pSender, EnSocketOperation enOperation, int iErrorCode, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pBuffer, int iLength);
};

