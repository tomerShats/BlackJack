#define WIN32_LEAN_AND_MEAN

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>



#include "realPlayer.h"
#include "Server.h"
#include "Inform.h"
#include "game.h"


#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"


using namespace std;


int main()
{
    int result;
    char buffer[BUFSIZ];
    enum_move mo;
    enum_result re;
    game* g = new game();
    g->start();
    do {
        result=g->startRound();
        if (result == 1) {
            break;
        }
        if (result != 2) {
            do {
                mo = g->waitToMove();
                if (mo == hit) {
                    result = g->hitMove();
                    if (result == 1) {
                        break;
                    }
                }
                else if (mo == toDouble) {
                    g->doubleMove();
                }
                else {
                    g->stayMove();
                }
            } while (mo == hit);
            if (g->check() != lose) {

                re = g->dealerMove();



            }

        }
        
        

    } while (1);

    delete g;
}

