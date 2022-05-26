/*
 * @Author: lawrence-cell 850140027@qq.com
 * @Generate Date: Do not edit
 * @LastEditors: lawrence-cell 850140027@qq.com
 * @LastEditTime: 2022-05-26 13:10:15
 * @FilePath: \UNO\src\CR\ui_manager_CR.h
 * @Description:
 *
 * Copyright (c) 2022 by lawrence-cell 850140027@qq.com, All Rights Reserved.
 */
#include "../ui/ui_manager.h"

namespace UNO
{
    namespace UI
    {
        // using namespace ui;

        class UIManager_CR : public UIManager
        {
        public:
            void RenderWhenInitWaiting(const std::vector<std::string> &usernames, bool isFirstTime);
        };

    } // namespace ui

} // namespace UNO
