/*
 * @Author: lawrence-cell 850140027@qq.com
 * @Generate Date: Do not edit
 * @LastEditors: lawrence-cell 850140027@qq.com
 * @LastEditTime: 2022-06-15 16:08:25
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

            void CalculateRank();

            int *GetRank() { return mRank; };

            friend class mSortStandard;

        private:
            std::vector<Card> mCompose;
            int mRank[3] = {0, 0, 0};
        };

        struct Composes
        {

            std::multiset<Compose, mSortStandard> mComposes;

            Composes();
            Composes(std::vector<Compose> composes);

            void Sort();

            template <typename T>
            void ReArrange(std::vector<T> &mSquence, int index1, int index2, int index3);
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
        };

    } // namespace gna

} // namespace UNO
