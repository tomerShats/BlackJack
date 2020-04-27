//
// Created by User on 3/25/2020.
//
#include <vector>
#include <string>
#include "player.h"

#ifndef BLACKJACK_BLACK_H
#define BLACKJACK_BLACK_H





class realPlayer : public player {
private:

    int perRoundCoins;
    
public:
    ~realPlayer();
    realPlayer();
    void doubleCoins();
    void setPerRoundCoins(int co);
    int getPerCoins();
    virtual void newRound(std::vector<int>& c);
    

};


#endif //BLACKJACK_BLACK_H
