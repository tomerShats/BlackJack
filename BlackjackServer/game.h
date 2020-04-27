#pragma once


    //
// Created by User on 3/25/2020.
//
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <vector>
#include <string>
#include "realPlayer.h"
#include "cpuPlayer.h"
#include "Server.h"
#include "Inform.h"

#ifndef BLACKJACK_GAME_H
#define BLACKJACK_GAME_H
    using namespace std;

    class game {
    private:
        realPlayer* real;
        cpuPlayer* cpu;
        vector<int>cards;
        iServer* server;
        NewGame m_newGame;
        cardsP m_cards;
        yourMove movePlayer;


    public:
        ~game();
        game();
        int start();
        int startRound();
        enum_move waitToMove();
        vector<int> getCards();
        void shuffleCards();
        void createCards();
        int hitMove();
        int doubleMove();
        void stayMove();
        enum_result dealerMove();
        enum_result check();
        enum_result checkDealer();
        enum_result checkEndGame();
        void playerLose();

    };




#endif //BLACKJACK_GAME_H



