#pragma once

#include <vector>
#include <utility>
#include <thread>
#include <functional>
#include <mutex>

#include "view.h"
#include "inputter.h"
#include "outputter.h"

namespace UNO
{
    namespace UI
    {

        using namespace Game;

        class UIManager
        {
        public:
            UIManager(std::unique_ptr<GameStat> &gameStat,
                      std::vector<PlayerStat> &playerStats,
                      std::unique_ptr<HandCards> &handCards,
                      std::unique_ptr<Composes> &composes);

            // ~UIManager() { mTimerThread->join(); }

            /**
             * Start the timer thread.
             */
            void RunTimerThread();

            /**
             * Stop the timer thread and wait for joining.
             */
            void StopTimerThread();

            /**
             * Render view when waiting for other players to join.
             */
            void RenderWhenInGame(const std::vector<std::string> &usernames);

            /**
             * Render view when game start.
             */
            void RenderWhenInitWaiting(const std::vector<std::string> &usernames, bool isFirstTime);

            /**
             * Render view in the main game loop.
             */
            void Render(bool useCls = true);

            void Render_CR(int single_game_compose_index, bool CursurinCardorComposebool, bool isFisrtInSingleGame = false);

            void test();

            /**
             * Get the player's action.
             */
            std::pair<InputAction, int> GetAction(bool lastCardCanBePlayed,
                                                  bool hasChanceToPlayAfterDraw);

            InputAction GetAction_CR(int single_game_compose_index);
            /**
             * Get the specified next color when a 'W' or '+4' is played.
             */
            CardColor SpecifyNextColor();

            /**
             * Ask player whether want to play again.
             */
            bool WantToPlayAgain(const std::string &winner);

            /**
             * Hook invoked when the game enters next turn.
             */
            void NextTurn();

            /**
             * Move the cursor in handcard to the position indicated by \param index.
             */
            void MoveCursorTo(int index) { mCursorIndex = index; }

            /**
             * To know other info, find HandlePlay() function.
             * Handle the keyboard input "enter" by \param index.
             */
            void HandleEnter();

            void HandleReady(bool &readytime);

            void RefreshCursur(int cursorIndex, const HandCards &handcards, bool CursurinCardorCompose);

        private:
            void TimerThreadLoop();

            void Print(bool useCls = true) const;

            void Print_CR(bool useCls = true) const;

            void ResetCursor() { MoveCursorTo(0); }

            void ResetTimeLeft() { mTimeLeft = Common::Common::mTimeoutPerTurn * 1000 + 500; }

            int PlayerNum() const { return mPlayerStats.size(); }

            void ExecuteWithTimePassing(const std::function<void()> &func);

        protected: //本来是private
            std::unique_ptr<View> mView;
            std::unique_ptr<Inputter> mInputter;
            std::unique_ptr<Outputter> mOutputter;

            std::unique_ptr<GameStat> &mGameStat;
            std::vector<PlayerStat> &mPlayerStats;
            std::unique_ptr<HandCards> &mHandCards;
            std::unique_ptr<Composes> &mComposes;

            int mCursorIndex{0};
            int mCursorIndexinCompose{0};
            int mTimeLeft; // in milliseconds

            std::unique_ptr<std::thread> mTimerThread;

            bool mLastCardCanBePlayed;
            bool mHasChanceToPlayAfterDraw;
            bool mIsSpecifyingNextColor{false};

            bool mTimerThreadShouldStop{false};
            // when printing view, it shouldn't be modified
            std::mutex mMutex;
        };
    }
}