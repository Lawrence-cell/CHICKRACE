#include "view.h"

namespace UNO
{
    namespace UI
    {

        const std::string View::CARDS_REMAINED_STR = "cards remained: ";
        const std::string View::LAST_PLAYED_STR = "last played: ";
        const std::string View::HAND_CARDS_STR = "handcards: ";
        const std::string View::UNO_STR = "UNO!";

        View::View()
        {
            auto [height, width] = ViewFormatter::GetMaxScaleOfView();
            mView.resize(height);
            for (auto &row : mView)
            {
                row.resize(width);
            }

            Clear(true);
        }

        void View::ClearForRefresh()
        {
            std::vector<int> rowNumToClear;
            auto [row, col] = ViewFormatter::GetPosOfPlayerBox(0);
            int singleBlockHeight = ViewFormatter::GetSingleHeightofBox();
            for (int i = 0; i < 4; i++)
            {
                rowNumToClear.emplace_back(row + 1 + singleBlockHeight + singleBlockHeight * i);
            }
            for (int row = 0; row < mView.size(); row++)
            {
                if (std::find(rowNumToClear.begin(), rowNumToClear.end(), row) != rowNumToClear.end())
                {
                    for (auto &c : mView[row])
                    {
                        c = ' ';
                    }
                }
            }
        }

        void View::Clear(bool para1, int para2)
        {

            for (int row = 0; row < mView.size(); row++)
            {

                for (auto &c : mView[row])
                {
                    c = ' ';
                }
            }
        }

        void View::DrawWhenInGame(const std::vector<std::string> &usernames)
        {
            for (int playerIndex = 0; playerIndex < Common::Common::mPlayerNum; playerIndex++)
            {

                // playerIndex代表的是哪个方块
                auto [row, col] = ViewFormatter::GetPosOfPlayerBox(playerIndex);
                auto [height, width] = ViewFormatter::GetBaseScaleOfBox(playerIndex);
                int singleBlockHeight = height / 2 - 1; // 单边block长度为2

                int absoluteIndex = Common::Util::WrapWithPlayerNum(playerIndex + mMyIndex);
                //取值范围： 0 - 2
                std::string cardExample = "R2  R2  Y2  W3  B2  G5  G2  G2  B3";
                std::string FirstComposeConfig = " >__<       __        __";

                if (playerIndex == 0)
                {
                    DrawBorder_InGameMine(row, col, width, singleBlockHeight);
                    AlignCenter(row + 1, col, width, usernames[absoluteIndex]);
                    AlignCenter(row + 1 + singleBlockHeight, col, width, cardExample);            //接收随机分发的九张卡牌
                    AlignCenter(row + 1 + singleBlockHeight * 2, col, width, FirstComposeConfig); //配牌选项 第一道
                    AlignCenter(row + 1 + singleBlockHeight * 3, col, width, FirstComposeConfig); //配牌选项 第二道
                    AlignCenter(row + 1 + singleBlockHeight * 4, col, width, FirstComposeConfig); //配牌选项 第二道
                }
                else
                {
                    DrawBorder(row, col, width, singleBlockHeight);
                    AlignCenter(row + 1, col, width, usernames[absoluteIndex]);
                    AlignCenter(row + 1 + singleBlockHeight, col, width, "PREPARE");
                }
            }
        }

        void View::DrawPhaseText(std::string phaseText)
        {
            auto [centerRow, centerCol] = ViewFormatter::GetBaseScaleOfView();
            // 20,70
            // std::cout << "runing" << std::endl;
            AlignCenter(centerRow * 1 / 3, 0, centerCol - 16, phaseText);
        }

        void View::DrawWhenInitWaiting(const std::vector<std::string> &usernames, bool isFirstTime)
        {
            DrawPhaseText("WAITTING PHASE");
            if (isFirstTime) // whether this function is first exec or not IN THE SAME CLIENT
            {
                mMyIndex = usernames.size() - 1;
                //第几个加入进来的客户端
            }
            for (int playerIndex = 0; playerIndex < Common::Common::mPlayerNum; playerIndex++)
            {

                // playerIndex代表的是哪个方块
                auto [row, col] = ViewFormatter::GetPosOfPlayerBox(playerIndex);
                auto [height, width] = ViewFormatter::GetBaseScaleOfBox(playerIndex);
                int singleBlockHeight = height / 2 - 1; // 单边block长度为2

                int curNum = usernames.size();
                //同一客户端第二次运行时 curNum变成2
                int absoluteIndex = Common::Util::WrapWithPlayerNum(playerIndex + mMyIndex);
                //取值范围： 0 - 2
                DrawBorder(row, col, width, singleBlockHeight); // height =6

                if (playerIndex == 0)
                {
                    AlignCenter(row + 1, col, width, usernames[absoluteIndex]);
                    if (curNum == 1)
                    {
                        AlignCenter(row + singleBlockHeight + 1, col, width, "Waiting for players to join game...");
                    }
                    else
                    {
                        AlignCenter(row + singleBlockHeight + 1, col, width, "READY!");
                    }
                }
                else
                {
                    if (absoluteIndex < curNum)
                    {
                        AlignCenter(row + 1, col, width, usernames[absoluteIndex]);
                        AlignCenter(row + singleBlockHeight + 1, col, width, "READY!");
                    }
                    else
                    {
                        AlignCenter(row + singleBlockHeight + 1, col, width, "WAITING");
                    }

                    // Copy(row + 3, col + 2, "WAITING");
                    // Copy(row + 3, col + 2, CARDS_REMAINED_STR);
                    // Copy(row + 4, col + 2, LAST_PLAYED_STR);
                }

                // if (absoluteIndex < curNum)
                // {
                //     ClearLinesInBlock(row + 3, col + 1, width);
                //     ClearLinesInBlock(row + 1, col + 1, width);
                //     AlignCenter(row + 3, col, width, "READY!");
                //     AlignCenter(row + 1, col, width, usernames[absoluteIndex]);
                // }
            }
        }

        //以单个方块为操作对象
        void View::DrawOtherBox_CR(int playerIndex, const GameStat &gameStat, const PlayerStat &playerStat)
        {
            //需要加入判断：如若收到
            bool isCurrentPlayer = false;
            auto [row, col] = ViewFormatter::GetPosOfPlayerBox(playerIndex);
            auto [height, width] = ViewFormatter::GetBaseScaleOfBox(playerIndex);
            int singleBlockHeight = height / 2 - 1;
            DrawBorder(row, col, width, singleBlockHeight);
            AlignCenter(row + 1, col, width, playerStat.GetUsername());
            AlignCenter(row + singleBlockHeight + 1, col, width, "CONFIGURING");
        }

        void View::DrawOtherBox(int playerIndex, const GameStat &gameStat, const PlayerStat &playerStat)
        {
            bool isCurrentPlayer = false;
            auto [row, col] = ViewFormatter::GetPosOfPlayerBox(playerIndex);
            auto [height, width] = ViewFormatter::GetBaseScaleOfBox(playerIndex);
            DrawBorderAndUsername(row, col, width, height - 2, playerStat.GetUsername());
            if (gameStat.GetCurrentPlayer() == playerIndex)
            {
                isCurrentPlayer = true;
            }
            // if (isCurrentPlayer) {
            // mView[row + 1][col + OTHER_BOX_WIDTH - 3] = '*';
            // }

            Copy(row + 3, col + 2, CARDS_REMAINED_STR);
            auto remainingHandCardsNum = playerStat.GetRemainingHandCardsNum();
            Copy(row + 3, col + 2 + CARDS_REMAINED_STR.size(), std::to_string(remainingHandCardsNum));
            if (remainingHandCardsNum == 1)
            {
                DrawUNO();
            }

            Copy(row + 4, col + 2, LAST_PLAYED_STR);
            if (playerStat.DoPlayInLastRound())
            {
                Copy(row + 4, col + 2 + LAST_PLAYED_STR.size(), playerStat.GetLastPlayedCard().ToString());
            }
        }

        void View::DrawSelfBox_CR(const GameStat &gameStat, const PlayerStat &playerStat,
                                  const HandCards &handcards, int cursorIndex, int single_game_compose_index)
        {
            // playerIndex代表的是哪个方块
            auto [row, col] = ViewFormatter::GetPosOfPlayerBox(0);
            auto [height, width] = ViewFormatter::GetBaseScaleOfBox(0);
            int singleBlockHeight = height / 2 - 1; // 单边block长度为2

            int absoluteIndex = Common::Util::WrapWithPlayerNum(0 + mMyIndex);
            //取值范围： 0 - 2

            std::string FirstComposeConfig = " __       __        __";

            DrawBorder_InGameMine(row, col, width, singleBlockHeight);
            DrawHandCards_CR(row + singleBlockHeight, col, width, handcards);
            AlignCenter(row + 1, col, width, playerStat.GetUsername());
            AlignCenter(row + 1 + singleBlockHeight * 2, col, width, FirstComposeConfig); //配牌选项 第一道
            AlignCenter(row + 1 + singleBlockHeight * 3, col, width, FirstComposeConfig); //配牌选项 第二道
            AlignCenter(row + 1 + singleBlockHeight * 4, col, width, FirstComposeConfig); //配牌选项 第二道

            auto [cardRow, cardCol] = ViewFormatter::GetPosOfHandCard_CR(cursorIndex, handcards);
            mView[cardRow][cardCol - 1] = '>';
        }

        void View::DrawSelfBox(const GameStat &gameStat, const PlayerStat &playerStat,
                               const HandCards &handcards, int cursorIndex)
        {
            // update mExtraRowNum first
            mExtraRowNum = Common::Util::GetSegmentNum(handcards.Number()) - 1;
            auto [row, col] = ViewFormatter::GetPosOfPlayerBox(0);
            auto [height, width] = ViewFormatter::GetBaseScaleOfBox(0);
            // int height = GetSelfBoxHeight();
            DrawBorderAndUsername(row, col, width, height - 2 + mExtraRowNum, playerStat.GetUsername());
            DrawHandCards(row, col, width, handcards);
            if (handcards.Number() == 1)
            {
                DrawUNO();
            }

            if (gameStat.IsMyTurn())
            {
                // mView[row + 1][col + width - 3] = '*';
                // show cursor only in the turn of player himself
                auto [cardRow, cardCol] = ViewFormatter::GetPosOfHandCard(cursorIndex, handcards);
                mView[cardRow][cardCol - 1] = '>';
            }
        }

        void View::DrawSelfTimeIndicatorIfNot()
        {
            auto [row, col] = ViewFormatter::GetPosOfPlayerBox(0);
            if (mView[row + 5 + mExtraRowNum][col] != '[')
            {
                DrawTimeIndicator(0, 0);
            }
        }

        void View::DrawLastPlayedCard(Card lastPlayedCard)
        {
            auto [row, col] = ViewFormatter::GetPosOfLastPlayedCard();
            Copy(row, col, lastPlayedCard.ToString());
        }

        void View::DrawUNO()
        {
            auto [row, col] = ViewFormatter::GetPosOfUNOText('U');
            Copy(row, col, UNO_STR);
        }

        void View::DrawTimeIndicator_CR(int timeElapsed)
        {
            std::string indicator(42, ' ');
            indicator.front() = '*';
            indicator.back() = '*';
            indicator.replace(1, timeElapsed, timeElapsed, '=');
            indicator[timeElapsed + 1] = '>';

            auto [row, col] = ViewFormatter::GetPosOfPlayerBox(0);
            row--;

            Copy(row, col, indicator);
            Copy(row, col, indicator);
        }

        void View::DrawTimeIndicator(int currentPlayer, int timeElapsed)
        {
            auto [row, col] = ViewFormatter::GetPosOfPlayerBox(currentPlayer);
            std::string indicator(18, ' ');
            indicator.front() = '[';
            indicator.back() = ']';
            indicator.replace(1, timeElapsed, timeElapsed, '=');
            indicator[timeElapsed + 1] = '>';

            if (currentPlayer != 0)
            {
                Copy(row + 6, col, indicator);
            }
            else
            {
                Copy(row + 5 + mExtraRowNum, col, indicator);
            }
        }

        void View::DrawHandCards_CR(int row, int col, int width, const HandCards &handcards)
        {

            AlignCenter(row + 1, col, width, handcards.ToStringBySegment(0));
        }

        void View::DrawHandCards(int row, int col, int width, const HandCards &handcards)
        {
            if (handcards.Number() > 0)
            {
                for (int i = 0; i < Common::Util::GetSegmentNum(handcards.Number()); i++)
                {
                    AlignCenter(row + 3 + i, col, width, handcards.ToStringBySegment(i));
                }
            }
            else
            {
                // you have won
                AlignCenter(row + 3, col, width, "You win!");
            }
        }

        void View::ClearLinesInBlock(int row, int col, int width)
        {
            for (int col = 0; col < width; col++)
            {
                mView[row][col] = ' ';
            }
        }

        void View::DrawBorder_InGameMine(int row, int col, int width, int singleBlockHeight)
        {
            DrawVerticalBorder(row + 1, col, singleBlockHeight * 5);
            DrawVerticalBorder(row + 1, col + width - 1, singleBlockHeight * 5);
            DrawHorizontalBorder(row, col, width);
            DrawHorizontalBorder(row + singleBlockHeight, col, width);
            DrawHorizontalBorder(row + singleBlockHeight * 2, col, width);
            DrawHorizontalBorder(row + singleBlockHeight * 3, col, width);
            DrawHorizontalBorder(row + singleBlockHeight * 4, col, width);
            DrawHorizontalBorder(row + singleBlockHeight * 5, col, width);
        }

        void View::DrawBorder(int row, int col, int width, int height)
        {
            // DrawHorizontalBorder(row + 1, col, width);
            //行数， 列数， 线的长度
            DrawVerticalBorder(row + 1, col, height * 2);
            DrawVerticalBorder(row + 1, col + width - 1, height * 2);
            DrawHorizontalBorder(row, col, width);
            DrawHorizontalBorder(row + height, col, width);
            DrawHorizontalBorder(row + height * 2, col, width);
        }

        /**
         * draw the border and username of a box, whose top left corner is located by \p row and \p col,
         * with width (including '+' at both sides) of \p width, height (not including '+' at both sides)
         * of \p height and username of \p username.
         */
        void View::DrawBorderAndUsername(int row, int col, int width, int height, const std::string &username)
        {
            DrawBorder(row, col, width, height);
            AlignCenter(row + 1, col, width, username);
        }

        /**
         * draw a horizontal border which starts at the position located by \p row and \p col,
         * and has a length of \p length, including '+' at both sides
         */
        void View::DrawHorizontalBorder(int row, int col, int length)
        {
            assert(length > 2);
            std::string border = "++";
            border.insert(1, length - 2, '-');
            Copy(row, col, border);
        }

        /**
         * draw a vertical border which starts at the position located by \p row and \p col,
         * and has a height of \p height, not including '+' at both sides
         */
        void View::DrawVerticalBorder(int row, int col, int height)
        {
            for (int i = 0; i < height; i++)
            {
                mView[row + i][col] = '|';
            }
        }

        void View::AlignCenter(int row, int col, int width, const std::string &src)
        {
            int indent = (width - src.size()) / 2;
            Copy(row, col + indent, src);
        }

        /**
         * copy the string \p src to the position in view located by \p row and \p col.
         * note that we use `strncpy` here instead of `strcpy`, that is because `strcpy`
         * copys the terminated-null too, which will cover the space following the string.
         * with `strncpy`, we can copy the string without the terminated-null.
         */
        void View::Copy(int row, int col, const std::string &src)
        {
            std::strncpy(mView[row].data() + col, src.c_str(), src.size());
        }

        std::ostream &operator<<(std::ostream &os, const View &view)
        {
            int rowNum = ViewFormatter::GetBaseScaleOfView().first + view.mExtraRowNum;
            std::for_each(view.mView.begin(), std::next(view.mView.begin(), rowNum),
                          [&os](const std::vector<char> &row)
                          {
                              for (auto c : row)
                              {
                                  os << c;
                              }
                              os << std::endl;
                          });
            return os;
        }

    }
}