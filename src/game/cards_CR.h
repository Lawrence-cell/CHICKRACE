// /*
//  * @Author: lawrence-cell 850140027@qq.com
//  * @Generate Date: Do not edit
//  * @LastEditors: lawrence-cell 850140027@qq.com
//  * @LastEditTime: 2022-05-23 09:57:15
//  * @FilePath: \UNO\src\game\cards_CHICKRACE.h
//  * @Description:
//  *
//  * Copyright (c) 2022 by lawrence-cell 850140027@qq.com, All Rights Reserved.
//  */
// #pragma once

// #include <iostream>
// #include <cassert>
// #include <vector>
// #include <array>
// #include <set>
// #include <deque>
// #include <algorithm>
// #include <random>
// namespace UNO
// {
//     namespace Game
//     {
//         enum class CardColor : uint8_t
//         {
//             BLACK,  //黑桃
//             RED,    //红桃
//             YELLOW, //梅花
//             GREEN   //方块
//         };

//         std::ostream &operator<<(std::ostream &os, const CardColor &color);

//         enum class CardText : uint8_t
//         {
//             A,
//             TWO,
//             THREE,
//             FOUR,
//             FIVE,
//             SIX,
//             SEVEN,
//             EIGHT,
//             NINE,
//             TEN,
//             JOKER,
//             QUEEN,
//             KING
//         };

//         struct Card
//         {
//             CardColor mColor;
//             CardText mText;

//             Card() {}
//             Card(const char *str);
//             Card(CardColor color, CardText text) : mColor(color), mText(text) {}

//             /**
//              * Check whether a card can be played after another one.
//              *   \param lastPlayedCard: the last card which is just played
//              *   \param isUno: whether the card to play is the last (final) one in the player's handcard
//              *   \return whether the card can played after the last played one
//              */
//             bool CanBePlayedAfter(Card lastPlayedCard, bool isUno = false);

//             /**
//              * Get the string format of a card, like 'W', 'R6', 'B+2'.
//              */
//             std::string ToString() const;

//             /**
//              * Get the length of the string format of the card, which can be 1, 2, or 3.
//              */
//             int Length() const;

//             static CardColor FromChar(char c);

//             bool operator<(const Card &rhs) const
//             {
//                 return (mColor < rhs.mColor) ||
//                        (mColor == rhs.mColor && mText < rhs.mText);
//             }

//             bool operator==(const Card &rhs) const
//             {
//                 return (mColor == rhs.mColor) && (mText == rhs.mText);
//             }

//             bool operator!=(const Card &card) const
//             {
//                 return !(*this == card);
//             }

//             friend std::ostream &operator<<(std::ostream &os, const Card &card);
//         };

//     } // namespace Game

// } // namespace UNO
