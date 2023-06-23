#pragma once
#include "stdafx.h"
#include <mysql.h>
using namespace std;

struct DB_USER
{
	struct USER
	{
		UINT Uin;
		string UserName;
		string PassWord;
		string LastAddr;
		string AddrDesc;
	};
};
struct DB_PLAYER
{
	struct PLAYER_ITEM
	{
		UINT Uin = 0;
		UINT ItemID = 0;
		UINT ItemNum = 0;
		UINT AvailPeriod = 0;
		UINT Status = 0;
		UINT ObtainTime = 0;
		UINT OtherAttribute = 0;
	};
	struct PLAYER_ROLE
	{
		UINT Uin = 0;
		string NickName = "";
		UINT Gender = 0;
		UINT Country = 0;
		UINT License = 0;
		UINT Experience = 0;
		UINT SpeedCoin = 0;
		UINT SuperMoney = 0;
		UINT Money = 0;
		UINT LuckMoney = 0;
		UINT WinNum = 0;
		UINT SecondNum = 0;
		UINT ThirdNum = 0;
		UINT TotalNum = 0;
		UINT CurHonor = 0;
		UINT TotalHonor = 0;
		UINT TodayHonor = 0;
		UINT RelaxTime = 0;
		UINT MonthDurationBefor = 0;
		UINT MonthDurationCur = 0;
		UINT Charm = 0;
		UINT DurationGame = 0;
		UINT DanceExp = 0;
		UINT Coupons = 0;
		UINT Admiration = 0;
		UINT TeamWorkExp = 0;
		UINT AchievePoint = 0;
		UINT RegTime = 0;
		string Signature = "";
	};
	struct KART_REFIT
	{
		UINT Uin = 0;
		UINT KartID = 0;
		UINT RefitCout = 0;
		UINT MaxFlags = 0;
		UINT WWeight = 0;
		UINT SpeedWeight = 0;
		UINT JetWeight = 0;
		UINT SJetWeight = 0;
		UINT AccuWeight = 0;
		UINT ShapeRefitCount = 0;
		UINT KartHeadRefitItemID = 0;
		UINT KartTailRefitItemID = 0;
		UINT KartFlankRefitItemID = 0;
		UINT KartTireRefitItemID = 0;
		UINT SecondRefitCount = 0;
		UINT Speed2Weight = 0;
		UINT DriftVecWeight = 0;
		UINT AdditionalZSpeedWeight = 0;
		UINT AntiCollisionWeight = 0;
		UINT LuckyValue = 0;
		UINT RefitLuckyValueMaxWeight = 0;
		UINT ShapeSuitID = 0;
		UINT LegendSuitLevel = 0;
		UINT LegendSuitLevelChoice = 0;
		UINT ShapeLegendSuitID = 0;
	};
	struct KART_SHAPE
	{
		UINT KartID = 0;
		string KartName = "";
		UINT ShapeSuitID = 0;
		UINT ShapeLegendSuitID = 0;
		string ShapeName = "";
	};
	struct KART_STONE
	{
		UINT ID = 0;
		UINT StoneGrooveID = 0;
		UINT StoneUseOccaType = 0;
		UINT SkillStoneID = 0;
	};
	struct KART_STONE_GROOVE
	{
		UINT Uin = 0;
		UINT KartID = 0;
		UINT ID = 0;
	};
	struct MAP_RECORD
	{
		UINT Uin = 0;
		UINT MapID = 0;
		UINT Record = 0;
		UINT LastUpdateTime = 0;
	};
	struct GIFT_BOX
	{
		UINT BoxID = 0;
		UINT ItemID = 0;
		string Name = "";
		UINT Weight = 0;
	};
	struct GIFT_ODDS
	{
		UINT BoxID = 0;
		UINT ItemID = 0;
		string Name = "";
		UINT Num = 0;
		UINT AvailPeriod = 0;
		UINT Weight = 0;
	};
	struct INFO_PET
	{
		UINT Uin = 0;
		UINT ID = 0;
		string Name = "";
		UINT Level = 0;
		UINT Streng_Level = 0;
		UINT Status = 0;
		struct PetSkill
		{
			UINT Active = 0;
			UINT SkillID = 0;
			UINT SkillValue = 0;
		}PetSkill[3];
	};
	struct INFO_PLAYER
	{
		UINT Uin = 0;
		UINT isInTopList = 0;
		UINT VipFlag = 0;
		UINT ExFlag = 0;
		UINT LastLoginTime = 0;
	};
	struct INFO_SHOP
	{
		UINT CommodityID = 0;
		string Name = "";
		UINT AvailPeriod = 0;
		UINT Price1 = 0;
		UINT Price2 = 0;
		UINT Price3 = 0;
		UINT Price4 = 0;
		UINT Price5 = 0;
		UINT Price6 = 0;
		UINT Num1 = 0;
		UINT Num2 = 0;
		UINT Num3 = 0;
		UINT Num4 = 0;
		UINT Num5 = 0;
		UINT Num6 = 0;
	};
};

class mMySQL
{
private:
	MYSQL mysql_user;
	MYSQL mysql_player;
	string host = "192.168.175.166";
	string user = "root";
	string pass = "123456";
	string db_user = "g_qqspeed_user";
	string db_player = "g_qqspeed_player";
	UINT port = 3306;

public:
	mMySQL();
	~mMySQL();

protected:
	void syncDB_USER_User(unordered_map<UINT, DB_USER::USER>& result);
	void syncDB_PLAYER_PlayerItem(vector<DB_PLAYER::PLAYER_ITEM>& result);
	void syncDB_PLAYER_PlayerRole(unordered_map<UINT, DB_PLAYER::PLAYER_ROLE>& result);
	void syncDB_PLAYER_KartRefit(vector<DB_PLAYER::KART_REFIT>& result);
	void syncDB_PLAYER_KartShape(vector<DB_PLAYER::KART_SHAPE>& result);
	void syncDB_PLAYER_KartStone(vector<DB_PLAYER::KART_STONE>& result);
	void syncDB_PLAYER_KartStoneGroove(vector<DB_PLAYER::KART_STONE_GROOVE>& result);
	void syncDB_PLAYER_MapRecord(vector<DB_PLAYER::MAP_RECORD>& result);
	void syncDB_PLAYER_GiftBox(unordered_map<UINT, DB_PLAYER::GIFT_BOX>& result);
	void syncDB_PLAYER_GiftOdds(vector<DB_PLAYER::GIFT_ODDS>& result);
	void syncDB_PLAYER_InfoPet(unordered_map<UINT, DB_PLAYER::INFO_PET>& result);
	void syncDB_PLAYER_InfoPlayer(unordered_map<UINT, DB_PLAYER::INFO_PLAYER>& result);
	void syncDB_PLAYER_InfoShop(unordered_map<UINT, DB_PLAYER::INFO_SHOP>& result);

	UINT MMYSQL_Register(const char* User, const char* Pass);
};

