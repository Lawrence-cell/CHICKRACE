/*
 * @Author: lawrence-cell 850140027@qq.com
 * @Generate Date: Do not edit
 * @LastEditors: lawrence-cell 850140027@qq.com
 * @LastEditTime: 2022-06-02 10:40:24
 * @FilePath: \UNO\src\ui\view_formatter.h
 * @Description:
 *
 * Copyright (c) 2022 by lawrence-cell 850140027@qq.com, All Rights Reserved.
 */
#pragma once

#include <utility>
#include <vector>

#include "../common/util.h"
#include "../game/cards.h"

namespace UNO
{
    namespace UI
    {

        class ViewFormatter
        {
        public:
            using PosT = std::pair<int, int>;
            using ScaleT = std::pair<int, int>;

        public:
            static void Init();

            static PosT GetPosOfPlayerBox(int playerIndex);

            static PosT GetPosOfPlayerBox_CR(int playerIndex);

            static PosT GetPosOfLastPlayedCard();

            static PosT GetPosOfUNOText(char c);

            static PosT GetPosOfPlayerLastPlayedCard(int playerIndex);

            static PosT GetPosOfHandCard(int handcardIndex, const Game::HandCards &handcards);

            static ScaleT GetBaseScaleOfView();

            static ScaleT GetMaxScaleOfView();

            static ScaleT GetBaseScaleOfBox(int playerIndex);

            static int GetSingleHeightofBox();

        private:
            static std::vector<std::vector<PosT>> mPosOfPlayerBox;
            static std::vector<PosT> mPosOfLastPlayedCard;
            static std::vector<ScaleT> mBaseScaleOfView;
            static std::vector<PosT> mPosOfUNOText;
        };

        struct RenderInfo
        {
            ViewFormatter::PosT mPos;
            Game::Card mCard;

            RenderInfo(const ViewFormatter::PosT &pos, Game::Card card)
                : mPos(pos), mCard(card) {}

            bool operator<(const RenderInfo &rhs) const
            {
                return (mPos.first < rhs.mPos.first) ||
                       (mPos.first == rhs.mPos.first && mPos.second < rhs.mPos.second);
            }
        };
    }
}