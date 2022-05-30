#pragma once

#include <memory>
#include <random>
#include <deque>
#include <cstdlib>

#include "stat.h"
#include "../network/server.h"
#include "game_board.h"
namespace UNO {
    namespace GTest {

        using namespace UNO::Network;

        class test_GameBoard:public GameBoard {
        public:
            //explicit GameBoard(std::shared_ptr<Network::IServer> serverSp);
            explicit test_GameBoard(std::shared_ptr<Network::IServer> serverSp);

            // test info recevie
            void test_info_recevie();



            /**
             * Broadcast info to players other than the current one.
             */
            template <typename ActionInfoT>
            void Broadcast(ActionInfoT& info) {
                int currentPlayer = mGameStat->GetCurrentPlayer();
                for (int i = 0; i < Common::Common::mPlayerNum; i++) {
                    if (i != currentPlayer) {
                        info.mPlayerIndex = Common::Util::WrapWithPlayerNum(currentPlayer - i);
                        mServer->DeliverInfo(&typeid(ActionInfoT), i, info);
                    }
                }
            }

        public:
            // for tests
            // const std::unique_ptr<Network::IServer> &GetServer() const { return mServer; }

            const std::unique_ptr<DiscardPile>& GetDiscardPile() const { return mDiscardPile; }

            const std::unique_ptr<Deck>& GetDeck() const { return mDeck; }

            const std::unique_ptr<GameStat>& GetGameStat() const { return mGameStat; }

            const std::vector<PlayerStat>& GetPlayerStats() const { return mPlayerStats; }

        private:
            std::shared_ptr<Network::IServer> mServer;

            // state of game board
            std::unique_ptr<DiscardPile> mDiscardPile;
            std::unique_ptr<Deck> mDeck;
            std::unique_ptr<GameStat> mGameStat;

            // state of all players
            std::vector<PlayerStat> mPlayerStats;
        };
    }
}