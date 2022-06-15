/*
 * @Author: lawrence-cell 850140027@qq.com
 * @Generate Date: Do not edit
 * @LastEditors: lawrence-cell 850140027@qq.com
 * @LastEditTime: 2022-06-15 16:09:07
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
                CalculateRank();
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

        Composes::Composes(std::vector<Compose> composes)
        {
            mComposes.insert(composes.begin(), composes.end());
        }

        void Composes::Sort()
        {

            // std::map<int, int> rankMap;
            // for (int i = 0; i < 3; i++)
            // {
            //     rankMap[mComposes[i].GetRank()]++;
            // }
            // switch (rankMap.size())
            // {
            // case 3:
            //     /* code */
            //     break;
            // case 2:
            //     break;
            // case 1:
            //     break;
            // default:
            //     break;
            // }
        }

        // 入参{a1 ,a2 ,a3}   3 1 2     结果： {a3, a1, a2}
        template <typename T>
        void Composes::ReArrange(std::vector<T> &nums, int a, int b, int c)
        {
            nums.push_back(nums[a]);
            nums.push_back(nums[b]);
            nums.push_back(nums[c]);
            nums.erase(nums.begin(), nums.begin() + 3);
        }

        void Compose::CalculateRank()
        {
        }
    } // namespace Game

} // namespace UNO
