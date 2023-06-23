#include "Message.h"

Message::Message(USHORT msgID, BYTE* body, size_t bodyLen, CacheUser* cacheUser, CachePlayer* cachePlayer) : MsgID(msgID), Body(body), BodyLen(bodyLen), pCacheUser(cacheUser), pCachePlayer(cachePlayer) {}

bool MMSG::SendToClient(ClientNode* Client, short MsgID, const BYTE* Data, DWORD Length, short SrcID, char SrcFE, short DstID, short MsgType, char Encrypt)
{
	bool ret = false;

	CSHEAD* ProtocolHead;
	MSGHEAD* MsgHead;
	void* MsgBody;
	int TotalLength;

	int MsgLen = sizeof(MSGHEAD) + Length;
	MsgHead = (MSGHEAD*)malloc(MsgLen);
	if (!MsgHead)
	{
		return ret;
	}
	MsgHead->MsgID = htons(MsgID);
	MsgHead->MsgType = htons(MsgType);
	MsgHead->MsgSeq = htonl(-1);
	MsgHead->SrcFE = SrcFE;
	MsgHead->DstFE = FE_CLIENT;
	MsgHead->SrcID = htons(SrcID);
	MsgHead->DstID = htons(DstID);
	MsgHead->BodyLen = htons(sizeof(USHORT) + USHORT(Length));
	MsgBody = (void*)(MsgHead + 1);
	memcpy(MsgBody, Data, Length);

	if (Encrypt)
	{
		int EncryptLen = oi_symmetry_encrypt2_len(MsgLen);
		TotalLength = sizeof(CSHEAD) + EncryptLen;
		if (!(ProtocolHead = (CSHEAD*)malloc(TotalLength)))
		{
			return ret;
		}
		oi_symmetry_encrypt2((BYTE*)MsgHead, MsgLen, Client->Key, (BYTE*)(ProtocolHead + 1), &EncryptLen);
		TotalLength = sizeof(CSHEAD) + EncryptLen;
	}
	else
	{
		TotalLength = sizeof(CSHEAD) + MsgLen;
		if (!(ProtocolHead = (CSHEAD*)malloc(TotalLength)))
		{
			return ret;
		}
		memcpy((MSGHEAD*)(ProtocolHead + 1), MsgHead, MsgLen);
	}
	free(MsgHead);

	ProtocolHead->TotalLength = htonl(TotalLength);
	ProtocolHead->Ver = htons(116);
	ProtocolHead->DialogID = htons(SrcID);
	ProtocolHead->Seq = htonl(-1);
	ProtocolHead->Uin = htonl(Client->Uin);
	ProtocolHead->BodyFlag = Encrypt;
	ProtocolHead->OptLength = 0;

#ifdef _DEBUG
	printf("[GameServer][ConnID:%d]SendMsg:%d\n", Client->ConnID, MsgID);
#endif
	ret = Client->Server->Send(Client->ConnID, (BYTE*)ProtocolHead, TotalLength);

	free(ProtocolHead);

	return ret;
}