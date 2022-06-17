/*
 * @Author: lawrence-cell 850140027@qq.com
 * @Generate Date: Do not edit
 * @LastEditors: lawrence-cell 850140027@qq.com
 * @LastEditTime: 2022-06-17 17:25:03
 * @FilePath: \UNO\src\ui\inputter.cpp
 * @Description:
 *
 * Copyright (c) 2022 by lawrence-cell 850140027@qq.com, All Rights Reserved.
 */
#include "inputter.h"

namespace UNO
{
    namespace UI
    {

        InputAction Inputter::GetAction(int timeout)
        {
            while (true)
            {
                char ch;
                try
                {
                    ch = Common::Util::GetCharWithTimeout(timeout, true);
                }
                catch (std::exception &e)
                {
                    // timeout
                    return InputAction::PASS;
                }

                switch (ch)
                {
                case ',':
                    return InputAction::CURSOR_MOVE_LEFT;
                case '.':
                    return InputAction::CURSOR_MOVE_RIGHT;
#if defined(__unix__) || defined(__APPLE__)
                case '\n':
                    return InputAction::PLAY;
#elif defined(_WIN32)
                case '\r':
                    return InputAction::ENTER;
#endif
                case ' ':
                    return InputAction::PASS;
                case 'q':
                case 'Q':
                    return InputAction::QUIT;
                case '1':
                    return InputAction::NUM1;
                case '2':
                    return InputAction::NUM2;
                case '3':
                    return InputAction::NUM3;
                case 'r':
                    return InputAction::READY;
                case 'R':
                    return InputAction::READY;
                case '\033':
                    return InputAction::ESC;
                case '\b':
                    return InputAction::BACKTOCARDS;
                }
            }
        }

        Game::CardColor Inputter::SpecifyNextColor(int timeout)
        {
            while (true)
            {
                char ch;
                try
                {
                    ch = Common::Util::GetCharWithTimeout(timeout, true);
                }
                catch (std::exception &e)
                {
                    // timeout, red is default
                    return Game::CardColor::RED;
                }

                switch (ch)
                {
                case 'R':
                case 'r':
                    return Game::CardColor::RED;
                case 'B':
                case 'b':
                    return Game::CardColor::BLACK;
                case 'F':
                case 'f':
                    return Game::CardColor::FLOWER;
                case 'S':
                case 's':
                    return Game::CardColor::SQUARE;
                }
            }
        }

    }
}