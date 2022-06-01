/*
 * @Author: lawrence-cell 850140027@qq.com
 * @Generate Date: Do not edit
 * @LastEditors: lawrence-cell 850140027@qq.com
 * @LastEditTime: 2022-05-23 11:53:52
 * @FilePath: \UNO\src\game\cards_CR.cpp
 * @Description:
 *
 * Copyright (c) 2022 by lawrence-cell 850140027@qq.com, All Rights Reserved.
 */

#include "cards_CR.h"
namespace UNO
{
    namespace Game
    {
        Card::Card(const char *str)
        {
            switch (*str)
            {
            case 'R':
                mColor = CardColor::RED;
                str++;
                break;
            case 'Y':
                mColor = CardColor::YELLOW;
                str++;
                break;
            case 'G':
                mColor = CardColor::GREEN;
                str++;
                break;
            case 'B':
                mColor = CardColor::BLACK;
                str++;
                break;
            default:
                mColor = CardColor::BLACK;
            }

            switch (*str)
            {
            case '1':
                str++;
                if (*str == '\0')
                {
                    mText = CardText::A;
                    break;
                }
                mText = CardText::TEN;
                break;
            case '2':
                mText = CardText::TWO;
                break;
            case '3':
                mText = CardText::THREE;
                break;
            case '4':
                mText = CardText::FOUR;
                break;
            case '5':
                mText = CardText::FIVE;
                break;
            case '6':
                mText = CardText::SIX;
                break;
            case '7':
                mText = CardText::SEVEN;
                break;
            case '8':
                mText = CardText::EIGHT;
                break;
            case '9':
                mText = CardText::NINE;
                break;
            case 'J':
                mText = CardText::JOKER;
                break;
            case 'Q':
                mText = CardText::QUEEN;
                break;
            case 'K':
                mText = CardText::KING;
                break;
            default:
                assert(0);
            }
        }

        std::string Card::ToString() const
        {
            std::string color;
            std::string text;

            switch (mColor)
            {
            case CardColor::RED:
                color = "R";
                break;
            case CardColor::YELLOW:
                color = "Y";
                break;
            case CardColor::GREEN:
                color = "G";
                break;
            case CardColor::BLACK:
                color = "B";
                break;
            default:
                assert(0);
            }

            switch (mText)
            {
            case CardText::A:
                text = "A";
                break;
            case CardText::TWO:
                text = "2";
                break;
            case CardText::THREE:
                text = "3";
                break;
            case CardText::FOUR:
                text = "4";
                break;
            case CardText::FIVE:
                text = "5";
                break;
            case CardText::SIX:
                text = "6";
                break;
            case CardText::SEVEN:
                text = "7";
                break;
            case CardText::EIGHT:
                text = "8";
                break;
            case CardText::NINE:
                text = "9";
                break;
            case CardText::TEN:
                text = "10";
                break;
            case CardText::JOKER:
                text = "J";
                break;
            case CardText::QUEEN:
                text = "Q";
                break;
            case CardText::KING:
                text = "K";
                break;
            default:
                assert(0);
            }

            return color.append(text);
        }

        int Card::Length() const
        {
            int length = 2;
            length += (mText == CardText::TEN ? 1 : 0);
            return length;
        }

        CardColor Card::FromChar(char c)
        {
            switch (c)
            {
            case 'R':
                return CardColor::RED;
            case 'Y':
                return CardColor::YELLOW;
            case 'G':
                return CardColor::GREEN;
            case 'B':
                return CardColor::BLACK;
            }
            assert(0);
        }
    } // namespace Game

} // namespace UNO
