/*
 * @Author: lawrence-cell 850140027@qq.com
 * @Generate Date: Do not edit
 * @LastEditors: lawrence-cell 850140027@qq.com
 * @LastEditTime: 2022-06-16 22:39:29
 * @FilePath: \UNO\src\ui\inputter.h
 * @Description:
 *
 * Copyright (c) 2022 by lawrence-cell 850140027@qq.com, All Rights Reserved.
 */
#pragma once

#include <string>
#include <iostream>

#include "../common/util.h"
#include "../game/cards.h"

namespace UNO
{
    namespace UI
    {

        enum class InputAction : uint8_t
        {
            CURSOR_MOVE_LEFT,
            CURSOR_MOVE_RIGHT,
            ENTER,
            PASS, // skip or draw
            QUIT,
            NUM1,
            NUM2,
            NUM3,
            ESC,
            READY,
            BACKTOCARDS
        };

        class Inputter
        {
        public:
            Inputter() {}

            /**
             * Wait for player to input an action with a time limit \param timeout.
             */
            InputAction GetAction(int timeout);

            /**
             * After the player plays a 'W' or '+4', he needs to specify the next color to turn to.
             */
            Game::CardColor SpecifyNextColor(int timeout);

        private:
        };

    }
}