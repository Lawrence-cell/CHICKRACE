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

namespace UNO
{
    namespace game
    {
        enum class CardColor : uint8_t
        {

            S, //方块
            F, //梅花
            R, //红心
            B  //黑桃
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
            ONE // A是最大的
        };
        /*
        牌型的集合
         */
        enum class Cardset : uint8_t
        {
            ORDINARY,       //普通牌型
            PAIRS,          //对子
            TRACTOR,        //顺子(拖拉机)
            SUITED,         //青子(清一色)
            STRAIGHT_FLUSH, //同花顺
            LEOPARD         //豹子
        };

        /*
        遍历数组的尝试
         */
        struct CardSet
        {
            const static std::set<CardColor> Cardcolors;
            const static std::set<CardText> CardTexts;
        };

        struct Card
        {
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

            //重载关系运算符用以实现牌组的自动排序，牌组的排序规则为，先比花色后比数字
            bool operator<(const Card &rhs) const
            {
                if (mColor < rhs.mColor)
                {
                    return true;
                }
                else if (mColor == rhs.mColor)
                {
                    return (mText < rhs.mText);
                }
                else
                {
                    return false;
                }
            }
        };

        /*
        手牌的排序规则为，先比花色再比数字
         */
        struct cmp
        {
        public:
            bool operator()(const Card &s1, const Card &s2) const
            {
                return (s1 < s2);
            }
        };

        /*
        牌组的排序规则，先比数字后比花色，方便表示顺子
         */
        struct cmp1
        {
        public:
            bool operator()(const Card &s1, const Card &s2) const
            {
                if (s1.mText < s2.mText)
                {
                    return true;
                }
                else if (s1.mText == s2.mText)
                {
                    if (s1.mColor < s2.mColor)
                    {
                        return true;
                    }
                }
                else
                {
                    return false;
                }
            }
        };

        class CardPair
        {
        public:
            /*
            将传入的Card类构造为牌组
             */
            CardPair(const std::set<Card> &cards);
            /*
            把本CardPair中的第i张与传入Cardpair中的第j张牌交换，限定条件由UI部分给出
            */
            void swapSet(CardPair &cardpile, int i, int j);

            /*
            判断该组牌是什么类型，返回的是Cardset中的枚举类型，且已经按大小排列好
             */

            Cardset cardForm() const;

            /*
            该函数将牌组里第i张牌移回手牌
             */

            Card remove(int i); //待写

            /*
            重载比较运算符判断牌组的大小
             */
            bool operator<(const CardPair &rhs) const
            {
                auto iterfirst = mPile.begin();
                auto iterSecond = mPile.begin()++;
                auto iterThird = mPile.end();
                //取出前面的内容和颜色
                int text1 = (int)((*iterfirst).mText);
                int text2 = (int)((*iterSecond).mText);
                int text3 = (int)((*iterThird).mText);
                CardColor color1 = (*iterfirst).mColor;
                CardColor color2 = (*iterSecond).mColor;
                CardColor color3 = (*iterThird).mColor;
                //取出后边的内容和颜色
                auto iterfirstBack = rhs.mPile.begin();
                auto iterSecondBack = rhs.mPile.begin()++;
                auto iterThirdBack = rhs.mPile.end();
                int text1Back = (int)((*iterfirstBack).mText);
                int text2Back = (int)((*iterSecondBack).mText);
                int text3Back = (int)((*iterThirdBack).mText);
                CardColor color1Back = (*iterfirstBack).mColor;
                CardColor color2Back = (*iterSecondBack).mColor;
                CardColor color3Back = (*iterThirdBack).mColor;
                Cardset set1 = this->cardForm();
                Cardset set2 = rhs.cardForm();
                if (set1 != set2)
                {
                    return set1 < set2;
                }

                else if (set1 == Cardset::PAIRS)
                { //中间必是对子
                    if (text2 != text2Back)
                    {
                        return text2 < text2Back;
                    }
                    else
                    {
                        return color2 < color2Back;
                    }
                }
                else
                {
                    if (text3 != text3Back)
                    {
                        return text3 < text3Back;
                    }
                    else if (text2 != text2Back)
                    {
                        return text2 < text2Back;
                    }
                    else if (text3 != text3Back)
                    {
                        return text3 < text3Back;
                    }
                    else
                        return color3 < color3Back;
                }
            }

        private:
            std::set<Card, cmp1> mPile; //不需要再另立一个最大牌面的属性，因为set已经排列好了
        };
        class HandCards
        {
        public:
            HandCards(const std::array<game::Card, 9> &cards);

            /*
            抽取一系列的的卡牌然后将他们添加到手牌上
             */
            void Draw(const std::vector<game::Card> &cards); //待写，因为没有抽牌的机会,具体看后面实现的情况

            /*
            从手牌中移除一张牌，为了添加到牌组中去
             */
            void Erase(int index);

            /*
            判断手牌是不是空的
             */
            bool Empty() const { return mCards.empty(); };

            /*
            返回某张卡牌在手中的序号，判断其是否存在有函数的Caller来判断
             */
            int getIndex(game::Card card) const;

            /*
            getter 获得卡牌中某个位置对应的Card对象
             */
            game::Card At(int index) const { return *IteratorAt(index); }

            /*
            返回指向set中特定元素的迭代器
             */
            std::set<game::Card, game::cmp>::iterator HandCards::IteratorAt(int index) const
            {
                auto it = std::begin(mCards);
                std::advance(it, index - 1);
                return it;
            }

            /*
            返回手牌中卡片的数量
             */
            int number() const { return mCards.size(); }

            /*
            将手牌输出为字符串方便实现文字界面如"R2"等
             */
            std::string ToString() const;

            /*
            将手牌以片段形式转化为字符
             */
            std::string ToStringBySegment(int seg) const; // 待写，因为暂时认为比鸡用不到片段输出

            // Length() 函数不用写因为在比鸡中所有的Text长度都为2

            /*
            清空手牌再来一局
             */
            void clear() { mCards.clear(); }

        private:
            std::set<game::Card, game::cmp> mCards; //初始手牌是一个先按照花色后按照大小排序的set
            std::string ToStringByCard(int start, int len) const;
        };

        class CardPile
        {
        protected:
            /*
            开始一局新游戏时将牌一张张地输入进牌组
             */
            template <typename... Types>
            void PushFront(Types... args)
            {
                mPile.emplace_front(ars...);
            }

            /*
            每发一张牌，就从牌对顶部移除一张牌，并将其作为返回值返回
             */
            game::Card popFront()
            {
                game::Card card = mPile.front();
                mPile.pop_front();
                return card;
            }

            /*
            在牌堆前边添加一张牌
             */
            template <typename... Types>
            void pushFront(Types... args)
            {
                mPile.emplace_front(args...);
            }

            /*
            将牌堆中的最后一张牌移除并作为返回值返回
             */
            game::Card popBack()
            {
                game::Card card = mPile.back();
                mPile.pop_back();
                return card;
            }
            /*
            将牌堆的排序洗乱
             */
            void Shuffle()
            {
                std::random_device rd;
                std::mt19937 g(rd());
                std::shuffle(mPile.begin(), mPile.end(), g);
            }

            /*
            与目标牌堆交换
             */
            void swap(CardPile &pile) { std::swap(mPile, pile.mPile); };

            /*
            清空牌堆
             */
            void clear() { mPile.clear(); };

            /*
            Empty函数判断是否为空没有写，因为觉得可能用不到
             */

        private:
            std::deque<game::Card> mPile;
        };

        /*
        弃牌堆没有写，因为可能用不上
         */

        class Deck : public CardPile
        {
        public:
            /*
            初始化牌堆为52张牌并洗牌
             */
            void Init();

            /*
            将九张牌添加到每个玩家的初始手牌
             */
            std::vector<std::array<game::Card, 9>> DealInitHandCards(int playerNum);

            /*
            Draw函数抽牌没写因为可能用不到
             */
            Card Draw();
            /*
            抽n张卡函数没写因为可能用不到
             */

            /*
            添加一张牌到牌堆的底部没写因为可能用不到
             */
        };

    }
}