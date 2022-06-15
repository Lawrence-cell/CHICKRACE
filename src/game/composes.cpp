/*
 * @Author: lawrence-cell 850140027@qq.com
 * @Generate Date: Do not edit
 * @LastEditors: lawrence-cell 850140027@qq.com
 * @LastEditTime: 2022-06-16 01:45:21
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

        std::map<CardText, int> mMap = {
            {CardText::TWO, 1}, {CardText::THREE, 2}, {CardText::FOUR, 3}, {CardText::FIVE, 4}, {CardText::SIX, 5}, {CardText::SEVEN, 6}, {CardText::EIGHT, 7}, {CardText::NINE, 8}, {CardText::TEN, 9}, {CardText::JOKER, 10}, {CardText::QUEEN, 11}, {CardText::KING, 12}, {CardText::ACE, 13}};
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
                CalculateTotalPoint();
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
            // std::vector<Card> &a = mCompose;
            // int len = a.size();
            // for (int i = 0; i < len - 1; i++) //需要循环次数
            // {
            //     for (int j = 0; j < len - 1 - i; j++) //每次需要比较个数
            //     {
            //         if (mMap[a[j].mText] > mMap[a[j + 1].mText])
            //         {
            //             std::swap(a[j], a[j + 1]); //不满足偏序，交换
            //         }
            //     }
            // }

            std::vector<int> cardValue;
            for (int i = 0; i < 3; i++)
            {
                cardValue.emplace_back(mMap[mCompose[i].mText]);
            }

            auto maxIterator = std::max_element(std::begin(cardValue), std::end(cardValue));
            auto minIterator = std::min_element(std::begin(cardValue), std::end(cardValue));
            int maxIndex = maxIterator - cardValue.begin();
            int minIndex = minIterator - cardValue.begin();
            int midIndex = 3 - maxIndex - minIndex;

            ReArrange<Card>(mCompose, maxIndex, midIndex, minIndex);

            // std::swap(mCompose[maxIndex], mCompose[2]);
        }

        void Compose::SetRank(int r1, int r2, int r3)
        {

            mRank[0] = r1;
            mRank[1] = r2;
            mRank[2] = r3;
            // std::vector<CardColor> colorList;
            // std::vector<CardText> textList;

            // std::map<CardColor, int> mColorRankMap = {
            //     {CardColor::BLACK, 4}, {CardColor::RED, 3}, {CardColor::FLOWER, 2}, {CardColor::SQUARE, 1}};
            // for (auto it = mCompose.begin(); it != mCompose.end(); it++)
            // {
            //     colorList.emplace_back(it->mColor);
            //     textList.emplace_back(it->mText);
            // }

            // if (colorList[0] == colorList[1] && colorList[1] == colorList[2])
            // {
            //     if (textList[0] == textList[1] && textList[1] == textList[2])
            //     {
            //         mRank[0] = 6;
            //         mRank[1] = mMap[textList[1]];
            //         mRank[2] = mColorRankMap[colorList[1]];
            //     }
            //     else if (/* condition */)
            //     {
            //         /* code */
            //     }
            //     else
            //     {
            //         mRank[0] = 4;
            //         mRank[1] = mMap[textList[0]];
            //         mRank[2] = mColorRankMap[colorList[0]];
            //     }
            // }
            // else if (/* condition */)
            // {
            //     /* code */
            // }
        }

        void Composes::Sort()
        {
            std::vector<Compose *> &a = mComposes;

            int len = a.size();
            for (int i = 0; i < len - 1; i++) //需要循环次数
            {
                for (int j = 0; j < len - 1 - i; j++) //每次需要比较个数
                {
                    if (a[j]->GetTotalPoint() > a[j + 1]->GetTotalPoint())
                    {
                        std::swap(a[j], a[j + 1]); //不满足偏序，交换
                    }
                }
            }
        }

        // 入参{a1 ,a2 ,a3}   3 1 2     结果： {a3, a1, a2}
        template <typename T>
        void Compose::ReArrange(std::vector<T> &nums, int a, int b, int c)
        {
            nums.push_back(nums[a]);
            nums.push_back(nums[b]);
            nums.push_back(nums[c]);
            nums.erase(nums.begin(), nums.begin() + 3);
        }

        void Compose::CalculateTotalPoint()
        {
            int K3 = 1;
            int K2 = 5;
            int K1 = 14;

            totalPoint = K1 * mRank.at(0) + K2 * mRank.at(1) + K3 + mRank.at(2);
        }

        void Composes::Print()
        {
            for (int i = 0; i < 3; i++)
            {
                mComposes[i]->print();
            }
        }
    } // namespace Game

} // namespace UNO
