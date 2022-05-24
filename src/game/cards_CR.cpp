#include "Cards_CR.h"

namespace CHICKRACE{
    namespace game{
        /* 
        重载输出函数，可能用于UI的界面输出
         */
        std::ostream &operator<<(std::ostream &os, const CardColor &color)
        {
            std::string colorStr;
            switch (color)
            {
            case CardColor::B:
                colorStr = "B";
                break;
            case CardColor::R:
                colorStr = "R";
                break;
            case CardColor::F:
                colorStr = "F";
                break;
            case CardColor::S:
                colorStr = "S";
                break;
            default:
                assert(0);
            }

            os << colorStr;
            return os;
        }

        /* 
        Card的构造函数，传入一个长度为2的字符串，第一个代表颜色，第二个代表内容，其中0代表10
         */
        Card::Card(const std::string str){
            switch (str.at(0))
            {
            case 'B':
                this->mColor=CardColor::B;
                break;
            case 'R':
                this->mColor=CardColor::R;
                break;
            case 'F':
                this->mColor=CardColor::F;
                break;
            case 'S':
                this->mColor=CardColor::S;
                break;
            default:
                std::cout<<"传入数据错误";
                assert(0);
            }
            switch (str.at(1))
            {
            case '1':
                this->mText=CardText::ONE;
                break;
            case '2':
                this->mText=CardText::TWO;
                break;
            case '3':
                this->mText=CardText::THREE;
                break;
            case '4':
                this->mText=CardText::FOUR;
                break;
            case '5':
                this->mText=CardText::FIVE;
                break;    
            case '6':
                this->mText=CardText::SIX;
                break;
            case '7':
                this->mText=CardText::SEVEN;
                break;
            case '8':
                this->mText=CardText::EIGHT;
                break;
            case '9':
                this->mText=CardText::NINE;
                break;
            case '0':
                this->mText=CardText::TEN;
                break;
            case 'J':
                this->mText=CardText::JACK;
                break;
            case 'Q':
                this->mText=CardText::FOUR;
                break;
            case 'K':
                this->mText=CardText::KING;
                break;
            default:
                std::cout<<"传入数据错误";
                assert(0);
            }
        }

        std::string Card::ToString() const{
            std::string color;
            std::string text;
            switch (mColor)
            {
            case CardColor::B:
                color='B';
                break;
            case CardColor::R:
                color='R';
                break;
            case CardColor::F:
                color='F';
                break;
            case CardColor::S:
                color='S';
                break;
            
            default:
                assert(0);
            }
            switch (mText)
            {
            case CardText::ONE:
                text='1';
                break;
            case CardText::TWO:
                text='2';
                break;
            case CardText::THREE:
                text='3';
                break;
            case CardText::FOUR:
                text='4';
                break;
            case CardText::FIVE:
                text='5';
                break;
            case CardText::SIX:
                text='6';
                break;
            case CardText::SEVEN:
                text='7';
                break;
            case CardText::EIGHT:
                text='8';
                break;
            case CardText::NINE:
                text='9';
                break;
            case CardText::TEN:
                text='0';
                break;
            case CardText::JACK:
                text='J';
                break;
            case CardText::QUEEN:
                text='Q';
                break;
            case CardText::KING:
                text='K';
                break;
            default:
                assert(0);
            }
            return color.append(text);
        }

        void CardPair::swapSet(CardPair &cardpile,int i,int j){
            Card temp;
            auto iterThis=this->mPile.begin();
            auto iterThat=cardpile.mPile.begin();
            /* 
            指向被换元素
             */
            for(int t=1;t<i;t++){
                iterThis++;
            }
            for(int t=1;t<j;t++){
                iterThat++;
            }
            temp=*iterThis;
            this->mPile.erase(iterThis);
            this->mPile.emplace(*iterThat);
            cardpile.mPile.erase(iterThat);
            cardpile.mPile.emplace(temp);
        }

        CardPair::CardPair(const std::set<Card> &cards){
            auto iterThat=cards.begin();
            for(int i=0;i<3;i++){
                mPile.emplace(*iterThat);
                iterThat++;

            }
        }

        Cardset CardPair::cardForm()const{
            auto iterfirst=mPile.begin();
            auto iterSecond=mPile.begin()++;
            auto iterThird=mPile.end();
            //取出内容和颜色
            int text1=(int)((*iterfirst).mText);
            int text2=(int)((*iterSecond).mText);
            int text3=(int)((*iterThird).mText);
            CardColor color1=(*iterfirst).mColor;
            CardColor color2=(*iterSecond).mColor;
            CardColor color3=(*iterThird).mColor;


            //判断豹子
            if((text1==text2)&&(text2==text3)){
                return Cardset::LEOPARD;
            }
            //判断同花顺和清一色
            if((color1==color2)&&(color2==color3)){
                if((text1==text2-1)&&(text2==text3-1)){
                    return Cardset::STRAIGHT_FLUSH;
                }
                else{
                    return Cardset::SUITED;
                }
            }

            //判断顺子
            if((text1==text2-1)&&(text2==text3-1)){
                return Cardset::STRAIGHT_FLUSH;
            }

            //判断对子
            if((text1==text2)||(text2==text3)||(text1==text3)){
                return Cardset::PAIRS;
            }

            return Cardset::ORDINARY;
            
        }
    }
}