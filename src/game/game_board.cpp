#include <ctime>

#include "game_board.h"

namespace UNO
{
    namespace Game
    {

        GameBoard::GameBoard(std::shared_ptr<Network::IServer> serverSp)
            : mServer(serverSp),
              mDiscardPile(std::make_unique<DiscardPile>()),
              mDeck(std::make_unique<Deck>(*mDiscardPile))
        {
            mServer->RegisterReceiveJoinGameInfoCallback(
                [this](int index, const JoinGameInfo &info)
                {
                    ReceiveUsername(index, info.mUsername);
                });
            mServer->RegisterAllPlayersJoinedCallback([this]
                                                      { StartGame(); });
        }

        void GameBoard::Start()
        {
            mServer->Run();
        }

        std::shared_ptr<Network::IServer> GameBoard::CreateServer(const std::string &port)
        {
            return std::make_shared<Network::Server>(port);
        }

        void GameBoard::ResetGame()
        {
            mServer->Reset();
            mPlayerStats.clear();
        }

        void GameBoard::ReceiveUsername(int index, const std::string &username)
        {
            std::cout << "receive, index: " << index << ", username: " << username << std::endl;
            mPlayerStats.emplace_back(username, 9);
            std::vector<std::string> tmpUsernames;
            std::for_each(mPlayerStats.begin(), mPlayerStats.end(),
                          [&tmpUsernames](const PlayerStat &stat)
                          {
                              tmpUsernames.push_back(stat.GetUsername());
                          });
            Common::Util::Deliver<JoinGameRspInfo>(mServer, index, Common::Common::mPlayerNum, tmpUsernames);
            for (int i = 0; i < index; i++)
            {
                Common::Util::Deliver<JoinGameInfo>(mServer, i, username);
            }
        }

        void GameBoard::StartGame()
        {
#ifdef ENABLE_LOG
            spdlog::info("Game Starts.");
#endif
            mDeck->Init();
            std::vector<std::array<Card, 9>> initHandCards =
                mDeck->DealInitHandCards(Common::Common::mPlayerNum);

            // flip a card
            Card flippedCard;
            // while (true)
            // {
            //     flippedCard = mDeck->Draw();
            //     if (flippedCard.mColor == CardColor::BLACK)
            //     {
            //         // if the flipped card is a wild card, put it to under the deck and flip a new one
            //         mDeck->PutToBottom(flippedCard);
            //     }
            //     else
            //     {
            //         if (CardSet::DrawTexts.count(flippedCard.mText))
            //         {
            //             // last played card will become EMPTY if the flipped card is `Draw` card
            //             flippedCard.mText = CardText::JOKER;
            //         }
            //         break;
            //     }
            // }

            // choose the first player randomly
            std::srand(std::time(nullptr));
            int firstPlayer = std::rand() % Common::Common::mPlayerNum;

            std::vector<std::string> tmpUsernames;
            std::for_each(mPlayerStats.begin(), mPlayerStats.end(),
                          [&tmpUsernames](const PlayerStat &stat)
                          {
                              tmpUsernames.push_back(stat.GetUsername());
                          });
            for (int player = 0; player < Common::Common::mPlayerNum; player++)
            {
                Common::Util::Deliver<GameStartInfo>(mServer, player, initHandCards[player], flippedCard,
                                                     Common::Util::WrapWithPlayerNum(firstPlayer - player), tmpUsernames);

                std::rotate(tmpUsernames.begin(), tmpUsernames.begin() + 1, tmpUsernames.end());
            }

            mGameStat.reset(new GameStat(firstPlayer, flippedCard));
            GameLoop();
        }
        // p1[a1,a2,a3] 根据 a1 a2 a3 的大小 输出 a1 排第几 a2排排第几 a3排第几

        // p1[21, 12, 31] 21排第二 ,31排 第一, 12 排第三 输出 [2 ,0 , 1]

        // p1,p2,p3 都是 长度 为三  的int型vector
        //这三个数组是对齐的 索引为0的值是第一个玩家牌的总分 索引为1的值是第一个玩家牌的总分 索引为2的值是第一个玩家牌的总分
        // p1 = [u1,u2,u3] 计算出每一个玩家第一轮应该付的钱pay1(p1里值最大的玩家不用付钱， p1里值第二大的付10块 最小的付20)
        // p2 = [a1,a2,a3] 计算出每一个玩家第一轮应该付的钱pay2
        // p3 = [b1,b2,b3] 计算出每一个玩家第一轮应该付的钱pay3
        // 例如 p1 [2,1 ,3] 因为 第三个玩家值最大 所以pay= 0 第1个玩家次之 pay = 10 第二个玩家最小 pay = 20
        //那么得到的pay数组[]
        void GameBoard::CalculatePay(std::vector<int> &p1, std::vector<int> &p2, std::vector<int> &p3, std::array<int, 3> &payment)
        {
            std::vector<std::vector<int>> doubleList = {p1, p2, p3};
            for (int k = 0; k < 3; k++)
            {
                std::array<int, 3> index = {0, 1, 2};
                int len = 3;
                for (int i = 0; i < len - 1; i++) //需要循环次数
                {
                    for (int j = 0; j < len - 1 - i; j++) //每次需要比较个数
                    {
                        if (doubleList[k][j] > doubleList[k][j + 1])
                        {
                            std::swap(doubleList[k][j], doubleList[k][j + 1]);
                            std::swap(index[j], index[j + 1]); //不满足偏序，交换
                        }
                    }
                }
                //[2,1,0]
                payment[index[0]] -= 20;
                payment[index[1]] -= 10;
                payment[index[2]] += 30;
            }
        }

        void GameBoard::GameLoop()
        {

            while (!mGameStat->DoesGameEnd())
            {
                try
                {
                    std::vector<std::string> names;
                    std::vector<int> p1List;
                    std::vector<int> p2List;
                    std::vector<int> p3List;
                    std::array<int, 3> payment = {0, 0, 0};

                    for (int i = 0; i < 3; i++)
                    {
                        auto info = Common::Util::Receive<AllPlayersReadyInfo>(mServer, i);
                        std::string str(info->musername);
                        names.emplace_back(str);
                        p1List.emplace_back(info->mtotalPoints1);
                        p2List.emplace_back(info->mtotalPoints2);
                        p3List.emplace_back(info->mtotalPoints3);
                    }
                    CalculatePay(p1List, p2List, p3List, payment);
                    for (int i = 0; i < 3; i++)
                    {
                        Common::Util::Deliver<PayInfo>(mServer, i, names, payment);
                    }

                    // Common::Util::Deliver<GameStartInfo>(mServer, player, initHandCards[player], flippedCard,
                    //                                  Common::Util::WrapWithPlayerNum(firstPlayer - player), tmpUsernames);

                    // auto actionInfo = Common::Util::Receive<ActionInfo>(mServer, mGameStat->GetCurrentPlayer());
                    // switch (actionInfo->mActionType)
                    // {
                    // case ActionType::DRAW:
                    //     HandleDraw(Common::Util::DynamicCast<DrawInfo>(actionInfo));
                    //     break;
                    // case ActionType::SKIP:
                    //     HandleSkip(Common::Util::DynamicCast<SkipInfo>(actionInfo));
                    //     break;
                    // case ActionType::PLAY:
                    //     HandlePlay(Common::Util::DynamicCast<PlayInfo>(actionInfo));
                    //     break;
                    // default:
                    //     assert(0);
                    // }
                }
                catch (const std::exception &e)
                {
                    /// TODO: handle the condition that someone has disconnected
                    std::cout << "someone has disconnected, shutdown server" << std::endl;
                    std::exit(-1);
                }
            }
            ResetGame();
        }

        void GameBoard::HandleDraw(const std::unique_ptr<DrawInfo> &info)
        {
            std::cout << *info << std::endl;

            // draw from deck
            std::vector<Card> cardsToDraw = mDeck->Draw(info->mNumber);

            // respond to the deliverer
            Common::Util::Deliver<DrawRspInfo>(mServer, mGameStat->GetCurrentPlayer(),
                                               info->mNumber, cardsToDraw);

            // broadcast to other players
            Broadcast<DrawInfo>(*info);

            // update stat
            mPlayerStats[mGameStat->GetCurrentPlayer()].UpdateAfterDraw(info->mNumber);
            mGameStat->UpdateAfterDraw();
        }

        void GameBoard::HandleSkip(const std::unique_ptr<SkipInfo> &info)
        {
            std::cout << *info << std::endl;

            // broadcast to other players
            Broadcast<SkipInfo>(*info);

            // update stat
            mPlayerStats[mGameStat->GetCurrentPlayer()].UpdateAfterSkip();
            mGameStat->UpdateAfterSkip();
        }

        void GameBoard::HandlePlay(const std::unique_ptr<PlayInfo> &info)
        {
            std::cout << *info << std::endl;

            mDiscardPile->Add(info->mCard);
            if (info->mCard.mColor == CardColor::BLACK)
            {
                // change the color to the specified next color to show in UI
                info->mCard.mColor = info->mNextColor;
            }

            // broadcast to other players
            Broadcast<PlayInfo>(*info);

            // update stat
            PlayerStat &stat = mPlayerStats[mGameStat->GetCurrentPlayer()];
            stat.UpdateAfterPlay(info->mCard);
            if (stat.GetRemainingHandCardsNum() == 0)
            {
                Win();
            }
            mGameStat->UpdateAfterPlay(info->mCard);
        }

        void GameBoard::Win()
        {
            mGameStat->GameEnds();
#ifdef ENABLE_LOG
            spdlog::info("Game Ends.");
#endif
        }

    }
}