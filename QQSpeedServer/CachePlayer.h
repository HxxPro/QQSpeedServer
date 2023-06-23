#pragma once
#include "mMySQL.h"
class CachePlayer :
    public mMySQL
{
private:
    vector<DB_PLAYER::PLAYER_ITEM> pPlayerItem;
    std::unordered_map<UINT, DB_PLAYER::PLAYER_ROLE> mPlayerRole;
    vector<DB_PLAYER::KART_REFIT> pKartRefit;
    vector<DB_PLAYER::KART_SHAPE> pKartShape;
    vector<DB_PLAYER::KART_STONE> pKartStone;
    vector<DB_PLAYER::KART_STONE_GROOVE> pKartStoneGroove;
    vector<DB_PLAYER::MAP_RECORD> pMapRecord;
    std::unordered_map<UINT, DB_PLAYER::GIFT_BOX> mGiftBox;
    vector<DB_PLAYER::GIFT_ODDS> pGiftOdds;
    std::unordered_map<UINT, DB_PLAYER::INFO_PET> mInfoPet;
    std::unordered_map<UINT, DB_PLAYER::INFO_PLAYER> mInfoPlayer;
    std::unordered_map<UINT, DB_PLAYER::INFO_SHOP> mInfoShop;


public:
    CachePlayer();
    ~CachePlayer();

    void Sync();

    //check player's items
    bool PlayerItem_isPropExists(UINT Uin, UINT ItemID);
};

