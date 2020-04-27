//
// Created by User on 3/29/2020.
//
#include <vector>
#include <string>
#include "player.h"

#ifndef BLACKJACK_CPUPLAYER_H
#define BLACKJACK_CPUPLAYER_H


class cpuPlayer : public player {
public:
    ~cpuPlayer();
    cpuPlayer();
    virtual void newRound(std::vector<int>& c);
};


#endif //BLACKJACK_CPUPLAYER_H
