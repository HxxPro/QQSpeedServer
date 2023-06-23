#include "CacheUser.h"

CacheUser::CacheUser()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x06);
	Sync();
}

CacheUser::~CacheUser()
{
	mUser.clear();
}

void CacheUser::Sync()
{
	syncDB_USER_User(mUser);
}

int CacheUser::GetUinByUser(string User)
{
	UINT uin = 0;

	for (const auto& entry : mUser)
	{
		int key = entry.first;
		const DB_USER::USER& us = entry.second;

		if (us.UserName == User) uin = us.Uin;
	}
	if (uin == 0)
	{
		//not found
	}

	return uin;
}

bool CacheUser::GetUserInfoByUin(UINT Uin, DB_USER::USER& result)
{
	auto it = mUser.find(Uin);
	if (it != mUser.end())
	{
		const DB_USER::USER& user = it->second;
		result = user;
	}
	else
	{
		//not found
	}

	return false;
}

string CacheUser::GetUserByUin(UINT Uin)
{
	string result = "";

	auto it = mUser.find(Uin);
	if (it != mUser.end())
	{
		const DB_USER::USER& user = it->second;
		result = user.UserName;
	}
	else
	{
		//not found
	}

	return result;
}

string CacheUser::GetPassByUin(UINT Uin)
{
	string result = "";

	auto it = mUser.find(Uin);
	if (it != mUser.end())
	{
		const DB_USER::USER& user = it->second;
		result = user.PassWord;
	}
	else
	{
		//not found
	}

	return result;
}

bool CacheUser::cmpPassword(UINT Uin, string Pass)
{
	bool result = false;

	auto it = mUser.find(Uin);
	if (it != mUser.end())
	{
		const DB_USER::USER& user = it->second;
		if (user.PassWord == Pass) result = true;
	}
	else
	{
		//not found
	}

	return result;
}


bool CacheUser::Register(const char* User, const char* Pass)
{
	bool ret = false;

	UINT Uin = GetUinByUser(User);
	if (Uin == 0)
	{
		Uin = MMYSQL_Register(User, Pass);
		if (Uin != -1)
		{
			//cout << "NewID: " << Uin << endl;
			DB_USER::USER newUser;
			newUser.UserName = User;
			newUser.PassWord = Pass;
			newUser.LastAddr = "0";
			newUser.AddrDesc = "0";
			mUser[Uin] = newUser;

			ret = true;
		}
	}
	return ret;
}