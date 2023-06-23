#pragma once

#define KEY "swGaTmaHxcpW6dDz"

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <unordered_map>
#include <vector>
#include <memory>

#include "oicq/tea.h"
#include "HPSocket/HPSocket.h"
#include "yaml-cpp/yaml.h"
#include "utils/Utils.h"


struct ClientNode
{
	ITcpServer* Server;
	LONG_PTR BufferPtr;
	LONG_PTR BufferSize;
	LONG_PTR BufferOffset;
	int ConnID;

	BOOL IsLogin;
	DWORD Uin;
	BYTE Key[16];
	USHORT ServerID;
	UINT KartID;

	//Room
	USHORT RoomID;
	USHORT GameID;
	BOOL IsReady;

	//
	UINT MapID;
	int FinishTime;
	int TotalRound;
	int Round;
	int PassedCheckPoint;
	int EndCheckPoint;
	bool Loop;
	bool MapCompatibilityMode;

	//Dance
	int Scores;

	//Outdoor
	USHORT ChatRoomID;

};