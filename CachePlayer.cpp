#include "CachePlayer.h"

CachePlayer::CachePlayer()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x06);
	Sync();
}

CachePlayer::~CachePlayer()
{
}

void CachePlayer::Sync()
{
	syncDB_PLAYER_PlayerItem(pPlayerItem);
    syncDB_PLAYER_PlayerRole(mPlayerRole);
    syncDB_PLAYER_KartRefit(pKartRefit);
    syncDB_PLAYER_KartShape(pKartShape);
    syncDB_PLAYER_KartStone(pKartStone);
    syncDB_PLAYER_KartStoneGroove(pKartStoneGroove);
    syncDB_PLAYER_MapRecord(pMapRecord);
    syncDB_PLAYER_GiftBox(mGiftBox);
    syncDB_PLAYER_GiftOdds(pGiftOdds);
    syncDB_PLAYER_InfoPet(mInfoPet);
    syncDB_PLAYER_InfoPlayer(mInfoPlayer);
    syncDB_PLAYER_InfoShop(mInfoShop);
}

bool CachePlayer::PlayerItem_isPropExists(UINT Uin, UINT ItemID)
{
    bool ret = false;
    UINT count = pPlayerItem.size();

    if (count)
    {
        for (size_t i = 0; i < count; i++)
        {
            if (pPlayerItem[i].Uin == Uin && pPlayerItem[i].ItemID == ItemID)
            {
                ret = !ret;
                break;
            }
        }
    }

	return ret;
}
