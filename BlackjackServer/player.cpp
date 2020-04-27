//
// Created by User on 3/29/2020.
//
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include "player.h"

using namespace std;

player::player() {
    this->sum = 0;
}

player::~player() {

}

int player::getSumCards() {
    return this->sum;
}

void player::setSumCards() {
    int temp, countA = 0;
    this->sum = 0;
    for (std::vector<string>::iterator i = cards.begin(); i != cards.end(); i++) {
        if (*i == "2" || *i == "3" || *i == "4" || *i == "5" || *i == "6" || *i == "7" || *i == "8" || *i == "9" || *i == "10") {
            temp = stoi(*i);
            sum += temp;
        }
        else {
            if (*i != "A") {
                sum += 10;
            }
            else {
                countA++;
            }
        }

    }
    if (countA == 1) {
        if (sum + 11 > 21) {
            sum += 1;
        }
        else {
            sum += 11;
        }
    }
    else if (countA == 2) {
        if (sum + 12 > 21) {
            sum += 2;
        }
        else {
            sum += 12;
        }
    }
    else if (countA == 3) {
        if (sum + 13 > 21) {
            sum += 3;
        }
        else {
            sum += 13;
        }
    }
    else if (countA == 4) {
        if (sum + 14 > 21) {
            sum += 4;
        }
        else {
            sum += 14;
        }
    }

}

vector<string> player::getVector() {
    return this->cards;
}

void player::addCard(std::vector<int>& c) {

    int index;
    index = c.back();
    c.pop_back();
    if (index < 11) {
        cards.push_back(to_string(index));
    }
    else {
        if (index == 11) {
            cards.push_back("J");
        }
        else if (index == 12) {
            cards.push_back("Q");
        }
        else if (index == 13) {
            cards.push_back("K");
        }
        else {
            cards.push_back("A");
        }


    }

    this->setSumCards();
}

void player::clearVector() {
    this->cards.clear();
}