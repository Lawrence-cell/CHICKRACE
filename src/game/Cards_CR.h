#pragma once

#include <iostream>
#include <cassert>
#include <vector>
#include <array>
#include <set>
#include <deque>
#include <algorithm>
#include <random>
#ifdef ENABLE_LOG
#include <spdlog/spdlog.h>
#endif
#include "../common/common.h"


namespace CHICKRACE{
    namespace game{
        enum class CardColor : uint8_t
        {
            B,//黑桃
            R,//红心
            F,//梅花
            S//方块
        };
        std::ostream &operator<<(std::ostream &os, const CardColor &color);
        enum class CardText : uint8_t
        {
            ONE,
            TWO,
            THREE,
            FOUR,
            FIVE,
            SIX,
            SEVEN,
            EIGHT,
            NINE,
            TEN,
            JACK,
            QUEEN,
            KING
        };

        struct Card{
            CardColor mColor;
            CardText mText;
            Card(){};
            Card(const std::string str);
            Card(CardColor color, CardText text) : mColor(color), mText(text) {}
            /* 
            返回纸牌的字符类型如R2等
             */
            std::string ToString() const;

            /* 
            从字符返回CardColor枚举类型
             */
            static CardColor FromChar(char c);
            friend std::ostream &operator<<(std::ostream &os, const CardColor &color);
        }
        /* 
        牌组的排序规则为，先比数字后比花色
         */
        class cmp{
        public:
            bool operator()(const Card &s1,const Card &s2){
                if(s1.mText)
            }

        };
        class FirstPile{
        public:




        private:

            std::set<Card,cmp> mCards;
        };

    }
}