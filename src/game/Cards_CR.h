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
            KING,
            ONE//A是最大的
        };
        /* 
        牌型的集合
         */
        enum class Cardset:uint8_t
        {
            ORDINARY,//普通牌型
            PAIRS,//对子
            TRACTOR,//顺子(拖拉机)
            SUITED,//青子(清一色)
            STRAIGHT_FLUSH,//同花顺
            LEOPARD//豹子
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


        class CardPair{
        public:
            /* 
            将传入的Card类构造为牌组
             */
            CardPair(const std::set<Card> &cards);
            /* 
            把本CardPair中的第i张与传入Cardpair中的第j张牌交换，限定条件由UI部分给出
            */
            void swapSet(CardPair &cardpile,int i,int j);
            
            /* 
            判断该组牌是什么类型，返回的是Cardset中的枚举类型，且已经按大小排列好
             */

            Cardset cardForm() const;

            /* 
            判断牌组的大小
             */
            bool operator<(const CardPair &rhs) const{
                auto iterfirst=mPile.begin();
                auto iterSecond=mPile.begin()++;
                auto iterThird=mPile.end();
                //取出前面的内容和颜色
                int text1=(int)((*iterfirst).mText);
                int text2=(int)((*iterSecond).mText);
                int text3=(int)((*iterThird).mText);
                CardColor color1=(*iterfirst).mColor;
                CardColor color2=(*iterSecond).mColor;
                CardColor color3=(*iterThird).mColor;
                //取出后边的内容和颜色
                auto iterfirstBack=rhs.mPile.begin();
                auto iterSecondBack=rhs.mPile.begin()++;
                auto iterThirdBack=rhs.mPile.end();
                int text1Back=(int)((*iterfirstBack).mText);
                int text2Back=(int)((*iterSecondBack).mText);
                int text3Back=(int)((*iterThirdBack).mText);
                CardColor color1Back=(*iterfirstBack).mColor;
                CardColor color2Back=(*iterSecondBack).mColor;
                CardColor color3Back=(*iterThirdBack).mColor;
                Cardset set1=this->cardForm();
                Cardset set2=rhs.cardForm();
                if(set1!=set2){
                    return set1<set2;
                }

                else if (set1==Cardset::PAIRS){//中间必是对子
                if(text2 !=text2Back){
                    return text2 <text2Back;
                }
                else {
                    return color2 <color2Back;
                }


                }
                else {
                    if(text3!=text3Back){
                        return text3<text3Back;
                    }
                    else if (text2 != text2Back){
                        return text2<text2Back;
                    }
                    else if (text3 != text3Back){
                        return text3<text3Back;
                    }
                    else return color3 < color3Back;
                }
            }





        private:
            
            std::set<Card,cmp> mPile;//不需要再另立一个最大牌面的属性，因为set已经排列好了
        };

    }
    class HandCards{
    public:


    };
}