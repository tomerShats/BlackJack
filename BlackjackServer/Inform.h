#pragma once
#define WIN32_LEAN_AND_MEAN

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define MESSAGE_SIZE 8

using namespace std;


typedef enum { stillPlay, win, lose, tie }enum_result;
typedef enum { hit = 1, stay = 2, toDouble = 3 }enum_move;

typedef struct NewGame {
	int coins;
	bool stayToPlay;
}NewGame;

typedef struct result {
	enum_result r;
	int coins;

}result;


typedef struct cardsP {
	int sizeP;
	int sizeD;
	char myCards[MESSAGE_SIZE][MESSAGE_SIZE];
	char dealerCards[MESSAGE_SIZE][MESSAGE_SIZE];
	result struct_result;

}cardsP;

typedef struct yourMove {
	enum_move m;

}yourMove;

