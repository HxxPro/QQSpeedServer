#pragma once
#include "mMySQL.h"
class CacheUser :
    public mMySQL
{
private:
    std::unordered_map<UINT, DB_USER::USER> mUser;

public:
    CacheUser();
    ~CacheUser();

    void Sync();

    int GetUinByUser(string User);
    bool GetUserInfoByUin(UINT Uin, DB_USER::USER& result);
    string GetUserByUin(UINT Uin);
    string GetPassByUin(UINT Uin);
    bool cmpPassword(UINT Uin, string Pass);

    bool Register(const char* User, const char* Pass);
};

