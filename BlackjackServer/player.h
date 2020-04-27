//
// Created by User on 3/29/2020.
//
#include <vector>
#include <string>

#ifndef BLACKJACK_PLAYER_H
#define BLACKJACK_PLAYER_H


class player {
public:
    ~player();
    player();
    int getSumCards();
    void setSumCards();
    std::vector<std::string> getVector();
    void clearVector();
    virtual void newRound(std::vector<int>& c) = 0;
    void addCard(std::vector<int>& c);

private:
    std::vector<std::string>cards;
    int sum;




};


#endif //BLACKJACK_PLAYER_H
