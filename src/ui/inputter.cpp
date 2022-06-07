/*
 * @Author: lawrence-cell 850140027@qq.com
 * @Generate Date: Do not edit
 * @LastEditors: lawrence-cell 850140027@qq.com
 * @LastEditTime: 2022-06-07 00:49:10
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
                    return InputAction::PLAY;
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
                case 'R':
                    return InputAction::READY;
                case '\033':
                    return InputAction::ESC;
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
                case 'Y':
                case 'y':
                    return Game::CardColor::YELLOW;
                case 'G':
                case 'g':
                    return Game::CardColor::GREEN;
                case 'B':
                case 'b':
                    return Game::CardColor::BLUE;
                }
            }
        }

    }
}