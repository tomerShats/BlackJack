//
// Created by User on 3/29/2020.
//
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include "cpuPlayer.h"

cpuPlayer::cpuPlayer() {

}

cpuPlayer::~cpuPlayer() {
    this->getVector().clear();
}

void cpuPlayer::newRound(std::vector<int>& c) {
    if (this->getVector().empty() == false) {
        this->clearVector();
    }

    this->addCard(c);


}