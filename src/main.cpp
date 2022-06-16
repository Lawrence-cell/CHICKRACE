/*
 * @Author: lawrence-cell 850140027@qq.com
 * @Generate Date: Do not edit
 * @LastEditors: lawrence-cell 850140027@qq.com
 * @LastEditTime: 2022-06-16 12:23:35
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
#include "game/composes.h"
#include "common/util.h"
#include "common/config.h"
#include "CR/ui_manager_CR.h"

using namespace UNO;

Game::Compose *creatCompose(Game::Card card1, Game::Card card2, Game::Card card3)
{
    std::vector<Game::Card> cardList = {card1, card2, card3};
    auto composeptr = new Game::Compose(cardList);
    return composeptr;
}

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
        std::cout << "compose test begin" << std::endl;
        // std::unique_ptr<UNO::UI::HandCards> mHandCards;

        // // state of game board
        // std::unique_ptr<UNO::UI::GameStat> mGameStat;

        // // state of all players
        // std::vector<UNO::UI::PlayerStat> mPlayerStats;

        // std::vector<std::string> initUsernames = {"test a", "test b", "test c"};
        // auto mUIManager = std::make_unique<UNO::UI::UIManager>(mGameStat, mPlayerStats, mHandCards);
        // mUIManager->test();

        auto mCompose = new Game::Compose();
        auto card1 = new Game::Card(Game::CardColor::RED, Game::CardText::FOUR);
        auto card2 = new Game::Card(Game::CardColor::RED, Game::CardText::ACE);
        auto card3 = new Game::Card(Game::CardColor::RED, Game::CardText::JOKER);
        mCompose->AddCard(*card1);
        mCompose->AddCard(*card2);
        mCompose->AddCard(*card3);

        mCompose->print();
        mCompose->SortandPut();
        mCompose->print();

        // compose1->print();
        // compose1->SortandPut();
        // compose1->print();

        // auto card4 = new Game::Card(Game::CardColor::SQUARE, Game::CardText::FOUR);
        // auto card5 = new Game::Card(Game::CardColor::SQUARE, Game::CardText::ACE);
        // auto card6 = new Game::Card(Game::CardColor::SQUARE, Game::CardText::JOKER);
        // auto compose2 = creatCompose(*card4, *card5, *card6);

        // auto card7 = new Game::Card(Game::CardColor::BLACK, Game::CardText::FOUR);
        // auto card8 = new Game::Card(Game::CardColor::BLACK, Game::CardText::ACE);
        // auto card9 = new Game::Card(Game::CardColor::BLACK, Game::CardText::JOKER);
        // auto compose3 = creatCompose(*card7, *card8, *card9);

        // std::vector<Game::Compose *> list = {compose1, compose2, compose3};

        // auto combination = new Game::Composes(list);

        // compose1->CalculateTotalPoint();
        // compose2->CalculateTotalPoint();
        // compose3->CalculateTotalPoint();

        // combination->Print();
        // combination->Sort();
        // compose1->SortandPut();
        // compose2->SortandPut();
        // compose3->SortandPut();
        // std::cout << "!!!!!!!!!!!!" << std::endl;
        // combination->Print();
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