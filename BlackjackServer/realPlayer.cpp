//
// Created by User on 3/25/2020.
//
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include "realPlayer.h"

using namespace std;

realPlayer::realPlayer() {
    

}


void realPlayer::doubleCoins() {
    this->perRoundCoins = this->perRoundCoins * 2;
}



void realPlayer::setPerRoundCoins(int co) {
    this->perRoundCoins = co;
}


int realPlayer::getPerCoins() {
    return this->perRoundCoins;
}

void realPlayer::newRound(std::vector<int>& c) {
    if (this->getVector().empty() == false) {
        this->clearVector();
    }

    this->addCard(c);
    this->addCard(c);
}




realPlayer::~realPlayer() {
    this->getVector().clear();
}


