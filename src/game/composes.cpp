/*
 * @Author: lawrence-cell 850140027@qq.com
 * @Generate Date: Do not edit
 * @LastEditors: lawrence-cell 850140027@qq.com
 * @LastEditTime: 2022-06-14 23:56:22
 * @FilePath: \UNO\src\game\composes.cpp
 * @Description:
 *
 * Copyright (c) 2022 by lawrence-cell 850140027@qq.com, All Rights Reserved.
 */
#include "composes.h"

namespace UNO
{
    namespace Game
    {
        void Compose::AddCard(Card &card)
        {
            if (mCompose.size() == 3)
            {
                return; /* code */
            }
            else
            {
                mCompose.emplace_back(card);
            }
            if (mCompose.size() == 3)
            {
                SortandPut();
            }
        }

        Compose::Compose()
        {
        }

        void Compose::print()
        {
            for (int i = 0; i < 3; i++)
            {
                std::cout << mCompose[i].ToString() << std::endl;
            }
        }

        void Compose::SortandPut()
        {
            std::vector<int> cardValue;
            for (int i = 0; i < 3; i++)
            {
                cardValue.emplace_back((int)mCompose[i].mText);
            }

            auto maxIterator = std::max_element(std::begin(cardValue), std::end(cardValue));
            int maxIndex = &*maxIterator - &cardValue[0];
            std::swap(mCompose[maxIndex], mCompose[0]);
        }
    } // namespace Game

} // namespace UNO
