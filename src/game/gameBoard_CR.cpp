#include "gameBoard_CR.h";
#include <ctime>
namespace UNO {
    namespace GTest {

        test_GameBoard::test_GameBoard(std::shared_ptr<Network::IServer> serverSp)
            : mServer(serverSp),
            GameBoard(serverSp),
            mDiscardPile(std::make_unique<DiscardPile>()),
            mDeck(std::make_unique<Deck>(*mDiscardPile))
        {
            mServer->RegisterReceiveJoinGameInfoCallback(
                [this](int index, const JoinGameInfo& info) {
                    ReceiveUsername(index, info.mUsername);
                }
            );
            mServer->RegisterAllPlayersJoinedCallback([this] { test_info_recevie(); });
        }
        void test_GameBoard::test_info_recevie() {
                //auto actionInfo = Common::Util::Receive<JoinGameInfo>(mServer, mGameStat->GetCurrentPlayer());
            auto message = Common::Util::Receive<JoinGameInfo>(mServer, 1);
            std::cout << message << std::endl;
        }


    }
}