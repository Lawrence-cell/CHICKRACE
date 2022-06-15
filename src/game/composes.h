/*
 * @Author: lawrence-cell 850140027@qq.com
 * @Generate Date: Do not edit
 * @LastEditors: lawrence-cell 850140027@qq.com
 * @LastEditTime: 2022-06-16 01:39:47
 * @FilePath: \UNO\src\game\composes.h
 * @Description:
 *
 * Copyright (c) 2022 by lawrence-cell 850140027@qq.com, All Rights Reserved.
 */
#pragma

#include "cards.h"
namespace UNO
{
    namespace Game
    {
        class Compose
        {
        protected:
        public:
            Compose();
            Compose(const std::vector<Card> &cards) : mCompose(cards){};

            std::vector<Card> GetCompose()
            {
                return mCompose;
            }

            /**
             * @description: add a card in the end of this compose.
             * @param {Card} &card
             * @return {*}
             */
            void AddCard(Card &card);

            /**
             * @description:  delete a card from the end of this compose.
             * @return {*}
             */
            void DelCard();

            /**
             * @description:sort the compose figured, and put the biggest
             * one in the first position.
             * @return {*}
             */
            void SortandPut();

            /**
             * @description:
             * @return {*}
             */
            void print();

            /**
             * according to the cards combination to determine the rank
             * @return {*}
             */
            void CalculateTotalPoint();

            void SetRank(int r1, int r2, int r3);

            std::array<int, 3> GetRank() { return mRank; };

            int GetTotalPoint() { return totalPoint; }
            template <typename T>
            void ReArrange(std::vector<T> &mSquence, int index1, int index2, int index3);

            friend class mSortStandard;

        private:
            std::vector<Card> mCompose;
            std::array<int, 3> mRank;
            int totalPoint;
            // compose1 [1,2,3]
            // 1: [1-6] 2:[1-13] 3 : [1- 4]
            // k1 k2 k3
            // k3 =1 , k2 = 4
            // compose2 [1,3,4]
            // compose3 [2 ,3, 4]
        };

        class mSortStandard
        {
        public:
            bool operator()(const Compose &a1, const Compose &a2)
            {
                if (a1.mRank[0] == a2.mRank[0])
                {
                    if (a1.mRank[1] == a2.mRank[1])
                    {
                        return (a1.mRank[2]) < (a2.mRank[2]);
                    }
                    else
                    {
                        return (a1.mRank[1]) < (a2.mRank[1]);
                    }
                }
                else
                {
                    return (a1.mRank[0]) < (a2.mRank[0]);
                }
            }
            friend class Composes;
        };

        class Composes
        {
        public:
            Composes();
            Composes(std::vector<Compose *> composes) : mComposes(composes){};

            void Sort();

            std::vector<Compose *> GetComposes()
            {
                return mComposes;
            }

            void Print();

        private:
            std::vector<Compose *> mComposes;
        };

    } // namespace gna

} // namespace UNO
