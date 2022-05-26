/*
 * @Author: lawrence-cell 850140027@qq.com
 * @Generate Date: Do not edit
 * @LastEditors: lawrence-cell 850140027@qq.com
 * @LastEditTime: 2022-05-26 16:45:50
 * @FilePath: \UNO\src\CR\ui_manager_CR.cpp
 * @Description:
 *
 * Copyright (c) 2022 by lawrence-cell 850140027@qq.com, All Rights Reserved.
 */
#include "ui_manager_CR.h"

namespace UNO
{
    namespace UI
    {
        // using namespace ui;
        // using UIManager::UIManager;

        void UIManager_CR::RenderWhenInitWaiting(const std::vector<std::string> &usernames, bool isFirstTime, bool isCR)
        {

            for (int i = 0; i < 6; i++)
            {
                std::cout << '\n'
                          << Common::Util::WrapWithPlayerNum(i) << std::endl;
            }

            // mView->Clear(true);
            // mView->DrawWhenInitWaiting_CR(usernames, isFirstTime);
            // mOutputter->PrintRawView(*mView);
        }

    } // namespace ui

} // namespace UNO