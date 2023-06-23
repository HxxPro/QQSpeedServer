#include "stdafx.h"

#include "QQServer.h"
#include "GameServer.h"
#include "CacheUser.h"
#include "CachePlayer.h"

int main()
{
	SetConsoleTitle(TEXT("QQSpeedServer VERSION:0.7.1 - 2023.06.23"));

    std::string sign = R"(
________   ________    _________                        .____________                                
\_____  \  \_____  \  /   _____/_____   ____   ____   __| _/   _____/ ______________  __ ___________ 
 /  / \  \  /  / \  \ \_____  \\____ \_/ __ \_/ __ \ / __ |\_____  \_/ __ \_  __ \  \/ // __ \_  __ \
/   \_/.  \/   \_/.  \/        \  |_> >  ___/\  ___// /_/ |/        \  ___/|  | \/\   /\  ___/|  | \/
\_____\ \_/\_____\ \_/_______  /   __/ \___  >\___  >____ /_______  /\___  >__|    \_/  \___  >__|   
       \__>       \__>       \/|__|        \/     \/     \/       \/     \/                 \/       
)";

    std::cout << sign << std::endl;

    /*==================================================================================================*/


    CacheUser* pCacheUser = new CacheUser();
    CachePlayer* pCachePlayer = new CachePlayer();

    std::unique_ptr<QQServer> qqServer = std::make_unique<QQServer>();
    std::unique_ptr<GameServer> gameServer = std::make_unique<GameServer>(pCacheUser, pCachePlayer);

    qqServer->Run();
    gameServer->Run();


    return 0;
}