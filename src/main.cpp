/*
 * @Author: lawrence-cell 850140027@qq.com
 * @Generate Date: Do not edit
 * @LastEditors: lawrence-cell 850140027@qq.com
 * @LastEditTime: 2022-05-26 15:46:51
 * @FilePath: \UNO\src\main.cpp
 * @Description:
 *
 * Copyright (c) 2022 by lawrence-cell 850140027@qq.com, All Rights Reserved.
 */
#include <iostream>
#include <cxxopts.hpp>
#include <yaml-cpp/yaml.h>
#ifdef ENABLE_LOG
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#endif

#include "network/server.h"
#include "network/client.h"
#include "game/game_board.h"
#include "game/player.h"
#include "common/util.h"
#include "common/config.h"
#include "CR/ui_manager_CR.h"

using namespace UNO;

int main(int argc, char **argv)
{
    auto configInfo = Common::Config(argc, const_cast<const char **>(argv)).Parse();
#ifdef ENABLE_LOG
    spdlog::set_level(spdlog::level::info);
    spdlog::set_default_logger(spdlog::basic_logger_mt("UNO", configInfo->mLogPath));
    spdlog::default_logger()->flush_on(spdlog::level::info);
    spdlog::info("hello, spdlog");
#endif

    if (configInfo->test_mode)
    {
        std::cout << "ui test begin";
        std::unique_ptr<UNO::UI::HandCards> mHandCards;

        // state of game board
        std::unique_ptr<UNO::UI::GameStat> mGameStat;

        // state of all players
        std::vector<UNO::UI::PlayerStat> mPlayerStats;

        // initusername
        std::vector<std::string> initUsernames = {"test a", "test b", "test c"};
        auto mUIManager_CR = std::make_unique<UNO::UI::UIManager_CR>(mGameStat, mPlayerStats, mHandCards);
        mUIManager_CR->RenderWhenInitWaiting(initUsernames, true, true);
        system("pause");
        std::exit(0);
    }

    if (configInfo->mIsServer)
    {
        auto serverSp = Game::GameBoard::CreateServer(configInfo->mPort);
        Game::GameBoard gameBoard(serverSp);
        gameBoard.Start();
    }
    else
    {
        auto clientSp = Game::Player::CreateClient(configInfo->mHost, configInfo->mPort);
        Game::Player player(configInfo->mUsername, clientSp);
        player.Start();
    }

    return 0;
}