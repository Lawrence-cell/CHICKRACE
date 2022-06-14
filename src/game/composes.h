/*
 * @Author: lawrence-cell 850140027@qq.com
 * @Generate Date: Do not edit
 * @LastEditors: lawrence-cell 850140027@qq.com
 * @LastEditTime: 2022-06-15 00:02:48
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

        private:
            std::vector<Card> mCompose;
            int mRank;
        };

    } // namespace gna

} // namespace UNO
