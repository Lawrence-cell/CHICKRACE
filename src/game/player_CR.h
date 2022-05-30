#pragma once

#include"player.h"


namespace UNO {
    namespace GTEST {

        using namespace Network;
        using namespace UI;

        class test_Player :public Player {
        public:
            //explicit Player(std::string username, std::shared_ptr<Network::IClient> clientSp);
            explicit test_Player(std::string username, std::shared_ptr<Network::IClient> clientSp);

            //test deliver info
            void test_info_deliver();

        private:
            const std::string mUsername;
            std::string mWinner;
            std::shared_ptr<Network::IClient> mClient;

            std::unique_ptr<UIManager> mUIManager;
            std::unique_ptr<HandCards> mHandCards;

            // state of game board
            std::unique_ptr<GameStat> mGameStat;

            // state of all players
            std::vector<PlayerStat> mPlayerStats;
        };
    }
}
