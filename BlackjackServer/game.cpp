//
// Created by User on 3/25/2020.
//
#define _CRT_SECURE_NO_WARNINGS

#include "game.h"



game::game() {
    game::createCards();
    game::shuffleCards();
    game::shuffleCards();
}


int game::start() {
    this->cpu = new cpuPlayer();
    this->real = new realPlayer();
    this->server = new Server(3200);
    this->server->waitForNewClient();
    return 0;

}

int game::startRound()
{
    char buffer[BUFSIZ];
    int size = sizeof(m_newGame);
    memcpy(&m_newGame, server->receive(),size);
    if (m_newGame.stayToPlay == false) {
        return 1;
    }
    this->real->setPerRoundCoins(m_newGame.coins);
    this->real->newRound(this->cards);
    this->cpu->newRound(this->cards);
    for (int i = 0; i < this->real->getVector().size(); i++) {
        strcpy(m_cards.myCards[i], this->real->getVector().at(i).c_str());
    }
    for (int i = 0; i < this->cpu->getVector().size(); i++) {
        strcpy(m_cards.dealerCards[i], this->cpu->getVector().at(i).c_str());
    }
    if (this->real->getSumCards() == 21) {
        m_cards.struct_result.coins = this->real->getPerCoins();
        m_cards.struct_result.r = win;
        return 2;
    }
    else {
        m_cards.struct_result.r = stillPlay;
        
    }
    m_cards.sizeP = this->real->getVector().size();
    m_cards.sizeD = this->cpu->getVector().size();
    size = sizeof(m_cards);
    memcpy(&buffer, &m_cards, size);
    server->sendToClient(buffer, size);


    return 0;
}

enum_move game::waitToMove()
{
    char buffer[BUFSIZ];
    int size = sizeof(movePlayer);
    memcpy(&movePlayer, server->receive(), size);
    if (movePlayer.m == hit) {
        return hit;
    }else if(movePlayer.m == stay){
        return stay;
    }
    else {
        return toDouble;
    }

 }

game::~game() {
    delete real;
    delete cpu;
    server->closeServer();
}


vector<int> game::getCards() {
    return this->cards;
}

void game::shuffleCards() {
    srand(unsigned(std::time(0)));
    random_shuffle(cards.begin(), cards.end());
    random_shuffle(cards.begin(), cards.end());
    random_shuffle(cards.begin(), cards.end());
    random_shuffle(cards.begin(), cards.end());
}

void game::createCards() {
    int count = 0, j = 2;
    if (cards.empty() == false) {
        cards.clear();
    }
    for (int i = 0;i <= 207;i++) {
        if (count == 4 * 4) {
            count = 0;
            j++;
        }
        cards.push_back(j);
        count++;
    }

    game::shuffleCards();


}

int game::hitMove()
{
    char buffer[BUFSIZ];
    enum_result res;
    int size;
    this->real->addCard(this->cards);
    res=game::check();
    for (int i = 0; i < this->real->getVector().size(); i++) {
        strcpy(m_cards.myCards[i], this->real->getVector().at(i).c_str());
    }
    for (int i = 0; i < this->cpu->getVector().size(); i++) {
        strcpy(m_cards.dealerCards[i], this->cpu->getVector().at(i).c_str());
    }
    m_cards.sizeP = this->real->getVector().size();
    m_cards.sizeD = this->cpu->getVector().size();
    size = sizeof(m_cards);
    if (res ==lose) {
        m_cards.struct_result.r = lose;
        m_cards.struct_result.coins = this->real->getPerCoins() * (-1);
        memcpy(&buffer, &m_cards, size);
        server->sendToClient(buffer, size);
        return 1;
    }
    m_cards.struct_result.r = stillPlay;
    memcpy(&buffer, &m_cards, size);
    server->sendToClient(buffer, size);
    return 0;
}

int game::doubleMove()
{
    char buffer[BUFSIZ];
    enum_result res;
    int size;
    this->real->setPerRoundCoins(this->real->getPerCoins()*2);
    this->real->addCard(this->cards);
    res = game::check();
    for (int i = 0; i < this->real->getVector().size(); i++) {
        strcpy(m_cards.myCards[i], this->real->getVector().at(i).c_str());
    }
    for (int i = 0; i < this->cpu->getVector().size(); i++) {
        strcpy(m_cards.dealerCards[i], this->cpu->getVector().at(i).c_str());
    }
    m_cards.sizeP = this->real->getVector().size();
    m_cards.sizeD = this->cpu->getVector().size();
    size = sizeof(m_cards);
    if (res == lose) {
        m_cards.struct_result.r = lose;
        m_cards.struct_result.coins = this->real->getPerCoins() * (-1);
        memcpy(&buffer, &m_cards, size);
        server->sendToClient(buffer, size);
        return 1;
    }
    m_cards.struct_result.r = stillPlay;
    memcpy(&buffer, &m_cards, size);
    server->sendToClient(buffer, size);
    return 0;
}

void game::stayMove()
{
    char buffer[BUFSIZ];
    int size;
    for (int i = 0; i < this->real->getVector().size(); i++) {
        strcpy(m_cards.myCards[i], this->real->getVector().at(i).c_str());
    }
    for (int i = 0; i < this->cpu->getVector().size(); i++) {
        strcpy(m_cards.dealerCards[i], this->cpu->getVector().at(i).c_str());
    }
    m_cards.sizeP = this->real->getVector().size();
    m_cards.sizeD = this->cpu->getVector().size();
    size = sizeof(m_cards);
    m_cards.struct_result.r = stillPlay;
    memcpy(&buffer, &m_cards, size);
    server->sendToClient(buffer, size);

}

enum_result game::dealerMove()
{
    char buffer[BUFSIZ];
    int size;
    enum_result re;
    do {
        this->cpu->addCard(this->cards);
        re = game::checkDealer();
    } while (re == stillPlay);
    for (int i = 0; i < this->real->getVector().size(); i++) {
        strcpy(m_cards.myCards[i], this->real->getVector().at(i).c_str());
    }
    for (int i = 0; i < this->cpu->getVector().size(); i++) {
        strcpy(m_cards.dealerCards[i], this->cpu->getVector().at(i).c_str());
    }
    m_cards.sizeP = this->real->getVector().size();
    m_cards.sizeD = this->cpu->getVector().size();

    if (re == win) {
        re = game::checkEndGame();
    }
    else if (re == lose) {
        re = win;
    }

    if (re == lose) {
        this->real->setPerRoundCoins(this->real->getPerCoins() * (-1));
    }
    m_cards.struct_result.r = re;
    m_cards.struct_result.coins = this->real->getPerCoins();
    size = sizeof(m_cards);
    memcpy(&buffer, &m_cards, size);
    server->sendToClient(buffer, size);
    return re;
    
}

enum_result game::check()
{
    if (this->real->getSumCards() == 21) {
        return win;
    }
    else if(this->real->getSumCards() > 21){
        return lose;
    }
    else {
        return stillPlay;
    }
    
}

enum_result game::checkDealer()
{
    if (this->cpu->getSumCards() >= 17 && this->cpu->getSumCards()<=21) {
        return win;
    }
    else if (this->cpu->getSumCards() > 21) {
        return lose;
    }
    else {
        return stillPlay;
    }
    
}

enum_result game::checkEndGame()
{
    if (this->real->getSumCards() > this->cpu->getSumCards()) {
        return win;
    }
    else if (this->real->getSumCards() < this->cpu->getSumCards()) {
        return lose;
    }
    else {
        return tie;
    }
}

void game::playerLose()
{
    char buffer[BUFSIZ];
    int size;
    m_cards.struct_result.r = lose;
    m_cards.struct_result.coins = this->real->getPerCoins();
    size = sizeof(m_cards);
    memcpy(&buffer, &m_cards, size);
    server->sendToClient(buffer, size);

}
