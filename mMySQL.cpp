#include "mMySQL.h"

mMySQL::mMySQL()
{
}

mMySQL::~mMySQL() {}

void mMySQL::syncDB_USER_User(unordered_map<UINT, DB_USER::USER>& result)
{
	cout << "[SYNC]User..." << endl;

	MYSQL* conn;
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, host.c_str(), user.c_str(), pass.c_str(), db_user.c_str(), port, NULL, 0))
	{
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Execute query
	mysql_query(conn, "set names gbk");
	string query = "SELECT * FROM user;";
	if (mysql_query(conn, query.c_str()))
	{
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Get results
	MYSQL_RES* res = mysql_store_result(conn);
	if (!res) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Store results in vector
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		DB_USER::USER param;
		param.Uin = stoi(row[0]);
		param.UserName = row[1];
		param.PassWord = row[2];
		param.LastAddr = row[3];
		param.AddrDesc = row[4];
		//result.push_back(param);
		result[param.Uin] = param;
	}

	// Free resources
	mysql_free_result(res);
	mysql_close(conn);
}

void mMySQL::syncDB_PLAYER_PlayerItem(vector<DB_PLAYER::PLAYER_ITEM>& result)
{
	cout << "[SYNC]PlayerItem..." << endl;

	MYSQL* conn;
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, host.c_str(), user.c_str(), pass.c_str(), db_player.c_str(), port, NULL, 0)) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Execute query
	mysql_query(conn, "set names gbk");
	string query = "SELECT * FROM player_item;";

	if (mysql_query(conn, query.c_str()))
	{
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Get results
	MYSQL_RES* res = mysql_store_result(conn);
	if (!res) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}
	
	// Store results in vector
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		DB_PLAYER::PLAYER_ITEM param;
		param.Uin = stoi(row[0]);
		param.ItemID = stoi(row[1]);
		param.ItemNum = stoi(row[2]);
		param.AvailPeriod = stoi(row[3]);
		param.Status = stoi(row[4]);
		param.ObtainTime = stoi(row[5]);
		param.OtherAttribute = stoi(row[6]);
		result.push_back(param);
	}
	// Free resources
	mysql_free_result(res);
	mysql_close(conn);
}

void mMySQL::syncDB_PLAYER_PlayerRole(unordered_map<UINT, DB_PLAYER::PLAYER_ROLE>& result)
{
	cout << "[SYNC]PlayerRole..." << endl;

	MYSQL* conn;
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, host.c_str(), user.c_str(), pass.c_str(), db_player.c_str(), port, NULL, 0)) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Execute query
	mysql_query(conn, "set names gbk");
	string query = "SELECT * FROM player_role;";
	if (mysql_query(conn, query.c_str()))
	{
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Get results
	MYSQL_RES* res = mysql_store_result(conn);
	if (!res) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Store results in vector
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		DB_PLAYER::PLAYER_ROLE param;
		param.Uin = stoi(row[0]);
		param.NickName = row[1];
		param.Gender = stoi(row[2]);
		param.Country = stoi(row[3]);
		param.License = stoi(row[4]);
		param.Experience = stoi(row[5]);
		param.SpeedCoin = stoi(row[6]);
		param.SuperMoney = stoi(row[7]);
		param.Money = stoi(row[8]);
		param.LuckMoney = stoi(row[9]);
		param.WinNum = stoi(row[10]);
		param.SecondNum = stoi(row[11]);
		param.ThirdNum = stoi(row[12]);
		param.TotalNum = stoi(row[13]);
		param.CurHonor = stoi(row[14]);
		param.TotalHonor = stoi(row[15]);
		param.TodayHonor = stoi(row[16]);
		param.RelaxTime = stoi(row[17]);
		param.MonthDurationBefor = stoi(row[18]);
		param.MonthDurationCur = stoi(row[19]);
		param.Charm = stoi(row[20]);
		param.DurationGame = stoi(row[21]);
		param.DanceExp = stoi(row[22]);
		param.Coupons = stoi(row[23]);
		param.Admiration = stoi(row[24]);
		param.TeamWorkExp = stoi(row[25]);
		param.AchievePoint = stoi(row[26]);
		param.RegTime = stoi(row[27]);
		param.Signature = row[28];
		//result.push_back(param);
		result[param.Uin] = param;
	}

	// Free resources
	mysql_free_result(res);
	mysql_close(conn);
}

void mMySQL::syncDB_PLAYER_KartRefit(vector<DB_PLAYER::KART_REFIT>& result)
{
	cout << "[SYNC]KartRefit..." << endl;

	MYSQL* conn;
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, host.c_str(), user.c_str(), pass.c_str(), db_player.c_str(), port, NULL, 0)) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Execute query
	mysql_query(conn, "set names gbk");
	string query = "SELECT * FROM kart_refit;";

	if (mysql_query(conn, query.c_str()))
	{
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Get results
	MYSQL_RES* res = mysql_store_result(conn);
	if (!res) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Store results in vector
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		DB_PLAYER::KART_REFIT param;
		param.Uin = stoi(row[0]);
		param.KartID = stoi(row[1]);
		param.RefitCout = stoi(row[2]);
		param.MaxFlags = stoi(row[3]);
		param.WWeight = stoi(row[4]);
		param.SpeedWeight = stoi(row[5]);
		param.JetWeight = stoi(row[6]);
		param.SJetWeight = stoi(row[7]);
		param.AccuWeight = stoi(row[8]);
		param.ShapeRefitCount = stoi(row[9]);
		param.KartHeadRefitItemID = stoi(row[10]);
		param.KartTailRefitItemID = stoi(row[11]);
		param.KartFlankRefitItemID = stoi(row[12]);
		param.KartTireRefitItemID = stoi(row[13]);
		param.SecondRefitCount = stoi(row[14]);
		param.Speed2Weight = stoi(row[15]);
		param.DriftVecWeight = stoi(row[16]);
		param.AdditionalZSpeedWeight = stoi(row[17]);
		param.AntiCollisionWeight = stoi(row[18]);
		param.LuckyValue = stoi(row[19]);
		param.RefitLuckyValueMaxWeight = stoi(row[20]);
		param.ShapeSuitID = stoi(row[21]);
		param.LegendSuitLevel = stoi(row[22]);
		param.LegendSuitLevelChoice = stoi(row[23]);
		param.ShapeLegendSuitID = stoi(row[24]);
		result.push_back(param);
	}

	// Free resources
	mysql_free_result(res);
	mysql_close(conn);
}

void mMySQL::syncDB_PLAYER_KartShape(vector<DB_PLAYER::KART_SHAPE>& result)
{
	cout << "[SYNC]KartShape..." << endl;

	MYSQL* conn;
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, host.c_str(), user.c_str(), pass.c_str(), db_player.c_str(), port, NULL, 0)) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Execute query
	mysql_query(conn, "set names gbk");
	string query = "SELECT * FROM kart_shape;";
	if (mysql_query(conn, query.c_str()))
	{
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Get results
	MYSQL_RES* res = mysql_store_result(conn);
	if (!res) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Store results in vector
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		DB_PLAYER::KART_SHAPE param;
		param.KartID = stoi(row[0]);
		param.KartName = row[1];
		param.ShapeSuitID = stoi(row[2]);
		param.ShapeLegendSuitID = stoi(row[3]);
		param.ShapeName = row[4];
		result.push_back(param);
	}

	// Free resources
	mysql_free_result(res);
	mysql_close(conn);
}

void mMySQL::syncDB_PLAYER_KartStone(vector<DB_PLAYER::KART_STONE>& result)
{
	cout << "[SYNC]KartStone..." << endl;

	MYSQL* conn;
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, host.c_str(), user.c_str(), pass.c_str(), db_player.c_str(), port, NULL, 0)) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Execute query
	mysql_query(conn, "set names gbk");
	string query = "SELECT * FROM kart_stone;";

	if (mysql_query(conn, query.c_str()))
	{
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Get results
	MYSQL_RES* res = mysql_store_result(conn);
	if (!res) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Store results in vector
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		DB_PLAYER::KART_STONE param;
		param.ID = stoi(row[0]);
		param.StoneGrooveID = stoi(row[1]);
		param.StoneUseOccaType = stoi(row[2]);
		param.SkillStoneID = stoi(row[3]);
		result.push_back(param);
	}

	// Free resources
	mysql_free_result(res);
	mysql_close(conn);
}

void mMySQL::syncDB_PLAYER_KartStoneGroove(vector<DB_PLAYER::KART_STONE_GROOVE>& result)
{
	cout << "[SYNC]KartStoneGroove..." << endl;

	MYSQL* conn;
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, host.c_str(), user.c_str(), pass.c_str(), db_player.c_str(), port, NULL, 0)) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Execute query
	mysql_query(conn, "set names gbk");
	string query = "SELECT * FROM kart_stone_groove;";

	if (mysql_query(conn, query.c_str()))
	{
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Get results
	MYSQL_RES* res = mysql_store_result(conn);
	if (!res) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Store results in vector
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		DB_PLAYER::KART_STONE_GROOVE param;
		param.Uin = stoi(row[0]);
		param.KartID = stoi(row[1]);
		param.ID = stoi(row[2]);
		result.push_back(param);
	}

	// Free resources
	mysql_free_result(res);
	mysql_close(conn);
}

void mMySQL::syncDB_PLAYER_MapRecord(vector<DB_PLAYER::MAP_RECORD>& result)
{
	cout << "[SYNC]MapRecord..." << endl;

	MYSQL* conn;
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, host.c_str(), user.c_str(), pass.c_str(), db_player.c_str(), port, NULL, 0)) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Execute query
	mysql_query(conn, "set names gbk");
	string query = "SELECT * FROM map_record;";

	if (mysql_query(conn, query.c_str()))
	{
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Get results
	MYSQL_RES* res = mysql_store_result(conn);
	if (!res) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Store results in vector
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		DB_PLAYER::MAP_RECORD param;
		param.Uin = stoi(row[0]);
		param.MapID = stoi(row[1]);
		param.Record = stoi(row[2]);
		param.LastUpdateTime = stoi(row[3]);
		result.push_back(param);
	}

	// Free resources
	mysql_free_result(res);
	mysql_close(conn);
}

void mMySQL::syncDB_PLAYER_GiftBox(unordered_map<UINT, DB_PLAYER::GIFT_BOX>& result)
{
	cout << "[SYNC]GiftBox..." << endl;

	MYSQL* conn;
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, host.c_str(), user.c_str(), pass.c_str(), db_player.c_str(), port, NULL, 0)) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Execute query
	mysql_query(conn, "set names gbk");
	string query = "SELECT * FROM gift_box;";

	if (mysql_query(conn, query.c_str()))
	{
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Get results
	MYSQL_RES* res = mysql_store_result(conn);
	if (!res) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Store results in vector
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		DB_PLAYER::GIFT_BOX param;
		param.BoxID = stoi(row[0]);
		param.ItemID = stoi(row[1]);
		param.Name = row[2];
		param.Weight = stoi(row[3]);
		//result.push_back(param);
		result[param.BoxID] = param;
	}

	// Free resources
	mysql_free_result(res);
	mysql_close(conn);
}

void mMySQL::syncDB_PLAYER_GiftOdds(vector<DB_PLAYER::GIFT_ODDS>& result)
{
	cout << "[SYNC]GiftOdds..." << endl;

	MYSQL* conn;
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, host.c_str(), user.c_str(), pass.c_str(), db_player.c_str(), port, NULL, 0)) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Execute query
	mysql_query(conn, "set names gbk");
	string query = "SELECT * FROM gift_odds;";

	if (mysql_query(conn, query.c_str()))
	{
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Get results
	MYSQL_RES* res = mysql_store_result(conn);
	if (!res) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Store results in vector
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		DB_PLAYER::GIFT_ODDS param;
		param.BoxID = stoi(row[0]);
		param.ItemID = stoi(row[1]);
		param.Name = row[2];
		param.Num = stoi(row[3]);
		param.AvailPeriod = stoi(row[4]);
		param.Weight = stoi(row[5]);
		result.push_back(param);
	}

	// Free resources
	mysql_free_result(res);
	mysql_close(conn);
}

void mMySQL::syncDB_PLAYER_InfoPet(unordered_map<UINT, DB_PLAYER::INFO_PET>& result)
{
	cout << "[SYNC]InfoPet..." << endl;

	MYSQL* conn;
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, host.c_str(), user.c_str(), pass.c_str(), db_player.c_str(), port, NULL, 0)) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Execute query
	mysql_query(conn, "set names gbk");
	string query = "SELECT * FROM info_pet;";

	if (mysql_query(conn, query.c_str()))
	{
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Get results
	MYSQL_RES* res = mysql_store_result(conn);
	if (!res) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Store results in vector
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		DB_PLAYER::INFO_PET param;
		param.ID = stoi(row[0]);
		param.Name = row[1];
		param.Level = stoi(row[2]);
		param.Streng_Level = stoi(row[3]);
		param.Status = stoi(row[4]);

		param.PetSkill[0].SkillID = stoi(row[5]);
		param.PetSkill[1].SkillID = stoi(row[6]);
		param.PetSkill[2].SkillID = stoi(row[7]);

		param.PetSkill[0].SkillValue = stoi(row[8]);
		param.PetSkill[1].SkillValue = stoi(row[9]);
		param.PetSkill[2].SkillValue = stoi(row[10]);
		//result.push_back(param);
		result[param.ID] = param;
	}

	// Free resources
	mysql_free_result(res);
	mysql_close(conn);
}

void mMySQL::syncDB_PLAYER_InfoPlayer(unordered_map<UINT, DB_PLAYER::INFO_PLAYER>& result)
{
	cout << "[SYNC]InfoPlayer..." << endl;

	MYSQL* conn;
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, host.c_str(), user.c_str(), pass.c_str(), db_player.c_str(), port, NULL, 0)) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Execute query
	mysql_query(conn, "set names gbk");
	string query = "SELECT * FROM info_player;";

	if (mysql_query(conn, query.c_str()))
	{
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Get results
	MYSQL_RES* res = mysql_store_result(conn);
	if (!res) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Store results in vector
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		DB_PLAYER::INFO_PLAYER param;
		param.Uin = stoi(row[0]);
		param.isInTopList = stoi(row[1]);
		param.VipFlag = stoi(row[2]);
		param.ExFlag = stoi(row[3]);
		param.LastLoginTime = stoi(row[4]);
		//result.push_back(param);
		result[param.Uin] = param;
	}

	// Free resources
	mysql_free_result(res);
	mysql_close(conn);
}

void mMySQL::syncDB_PLAYER_InfoShop(unordered_map<UINT, DB_PLAYER::INFO_SHOP>& result)
{
	cout << "[SYNC]InfoShop..." << endl;

	MYSQL* conn;
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, host.c_str(), user.c_str(), pass.c_str(), db_player.c_str(), port, NULL, 0)) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Execute query
	mysql_query(conn, "set names gbk");
	string query = "SELECT * FROM info_shop;";
	if (mysql_query(conn, query.c_str()))
	{
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Get results
	MYSQL_RES* res = mysql_store_result(conn);
	if (!res) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	// Store results in vector
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		DB_PLAYER::INFO_SHOP param;
		param.CommodityID = stoi(row[0]);
		param.Name = row[1];
		param.AvailPeriod = stoi(row[2]);
		param.Price1 = stoi(row[3]);
		param.Price2 = stoi(row[4]);
		param.Price3 = stoi(row[5]);
		param.Price4 = stoi(row[6]);
		param.Price5 = stoi(row[7]);
		param.Price6 = stoi(row[8]);
		param.Num1 = stoi(row[9]);
		param.Num2 = stoi(row[10]);
		param.Num3 = stoi(row[11]);
		param.Num4 = stoi(row[12]);
		param.Num5 = stoi(row[13]);
		param.Num6 = stoi(row[14]);
		//result.push_back(param);
		result[param.CommodityID] = param;
	}

	// Free resources
	mysql_free_result(res);
	mysql_close(conn);
}

UINT mMySQL::MMYSQL_Register(const char* User, const char* Pass)
{
	MYSQL mysql;
	MYSQL_STMT* stmt = nullptr;
	UINT ret = -1;
	mysql_init(&mysql);
	mysql_real_connect(&mysql, host.c_str(), user.c_str(), pass.c_str(), db_user.c_str(), port, NULL, 0);
	stmt = mysql_stmt_init(&mysql); //创建MYSQL_STMT句柄


	mysql_query(&mysql, "set names gbk");

	const char* query = "INSERT INTO user(username, password, lastaddr, addrdesc) VALUES(?, ?, 0, 0);";
	if (mysql_stmt_prepare(stmt, query, strlen(query)))
	{
		return -1;
	}

	MYSQL_BIND params[2];
	memset(params, 0, sizeof(params));
	params[0].buffer_type = MYSQL_TYPE_STRING;
	params[0].buffer = (void*)User;
	params[0].buffer_length = strlen(User);
	params[1].buffer_type = MYSQL_TYPE_STRING;
	params[1].buffer = (void*)Pass;
	params[1].buffer_length = strlen(Pass);


	if (mysql_stmt_bind_param(stmt, params) != 0 || mysql_stmt_execute(stmt) != 0)
	{
		return -1;
	}
	else
	{
		// 获取插入操作生成的自增 ID
		ret = mysql_insert_id(&mysql);
	}
	mysql_stmt_close(stmt);
	mysql_close(&mysql);

	return ret;
}
