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
            
            S,//方块  
            F,//梅花 
            R,//红心 
            B//黑桃 
        };
        std::ostream &operator<<(std::ostream &os, const CardColor &color);
        enum class CardText : uint8_t
        {
            ONE=14,//A是最大的
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
            
            //重载关系运算符用以实现手牌的自动排序
             bool operator<(const Card &rhs) const{
                if (mText<rhs.mText){
                    return true;
                }
                else if (mText == rhs.mText){
                    return (mColor < rhs.mColor);
                }
                else{
                    return false;
                }
                
            }

        

            
        };
        /* 
        牌组的排序规则为，先比数字后比花色
         */
        struct cmp{
        public:
            bool operator()(const Card &s1,const Card &s2){
                return (s1<s2);
            }

        };
        class CardPile{
        public:
        /* 
        把本Cardpile中的第i张与传入Cardpile中的第j张牌交换，限定条件由UI部分给出
         */
        void swapSet(CardPile &cardpile,int i,int j);




        private:

            std::set<Card,cmp> mPile;
        };

    }
}