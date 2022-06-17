/*
 * @Author: lawrence-cell 850140027@qq.com
 * @Generate Date: Do not edit
 * @LastEditors: lawrence-cell 850140027@qq.com
 * @LastEditTime: 2022-06-17 15:37:35
 * @FilePath: \UNO\src\network\msg.h
 * @Description:
 *
 * Copyright (c) 2022 by lawrence-cell 850140027@qq.com, All Rights Reserved.
 */
#pragma once

// #include "../game/cards.h"
#include "../game/composes.h"

namespace UNO
{
    namespace Network
    {

        using namespace Game;

        enum class MsgType : uint8_t
        {
            JOIN_GAME,
            JOIN_GAME_RSP,
            GAME_START,
            ACTION,
            DRAW_RSP,
            GAME_END,
            All_READY,
            All_READY_RSP
        };

        struct Msg
        {
            MsgType mType;
            int mLen; // **not** include the mType and mLen itself
        };

        struct JoinGameMsg : public Msg
        {
            char mUsername[];
        };

        struct JoinGameRspMsg : public Msg
        {
            int mPlayerNum;
            // including player himself
            char mUsernames[];
        };

        struct GameStartMsg : public Msg
        {
            Card mInitHandCards[9];
            Card mFlippedCard; // indicating the first card that should be played
            int mFirstPlayer;  // the index of the first player to play a card
            // usernames of all players, not including player himself, ' ' as delimiter
            // and the order is from left side of the player to right side
            char mUsernames[];
        };

        struct AllPlayersReadyMsg : public Msg
        {
            int totalPoints1;
            int totalPoints2;
            int totalPoints3;
            char mUsernames[];
        };

        struct PayMsg : public Msg
        {
            int mPay[3];
            char mUsernames[];
        };

        enum class ActionType : uint8_t
        {
            DRAW,
            SKIP,
            PLAY
        };
        std::ostream &operator<<(std::ostream &os, const ActionType &type);

        struct ActionMsg : public Msg
        {
            ActionType mActionType;
            int mPlayerIndex;
        };

        struct DrawMsg : public ActionMsg
        {
            int mNumber; // the number of cards to draw
        };

        struct SkipMsg : public ActionMsg
        {
        };

        struct PlayMsg : public ActionMsg
        {
            Card mCard;
            CardColor mNextColor; // valid only if mCard is black
        };

        struct DrawRspMsg : public Msg
        {
            int mNumber;
            Card mCards[];
        };

        struct GameEndMsg : public Msg
        {
            int mWinner;
        };
    }
}