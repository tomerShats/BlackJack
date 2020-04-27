#undef UNICODE
#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
class iServer
{
protected:
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo myAdress;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    bool isServerReady;
public:
    iServer(unsigned short port)
    {
        isServerReady = true;
        // Initialize Winsock
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            printf("WSAStartup failed with error: %d\n", iResult);
            isServerReady = false;
            return;
        }

        //set my adress data
        ZeroMemory(&myAdress, sizeof(myAdress));
        myAdress.ai_family = AF_INET; //IPV4
        myAdress.ai_socktype = SOCK_STREAM; //TCP
        myAdress.ai_protocol = IPPROTO_TCP;
        myAdress.ai_flags = AI_PASSIVE;

        // Resolve the server address and port
        std::ostringstream oss;
        oss << port;

        iResult = getaddrinfo(NULL, oss.str().c_str(), &myAdress, &result);
        if (iResult != 0) {
            printf("getaddrinfo failed with error: %d\n", iResult);
            WSACleanup();
            isServerReady = false;
            return;
        }

        // Create a SOCKET for connecting to server
        ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (ListenSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            freeaddrinfo(result);
            WSACleanup();
            isServerReady = false;
            return;
        }

        // Setup the TCP listening socket
        iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            printf("bind failed with error: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            closesocket(ListenSocket);
            WSACleanup();
            isServerReady = false;
            return;
        }

        freeaddrinfo(result);

        iResult = listen(ListenSocket, SOMAXCONN);
        if (iResult == SOCKET_ERROR) {
            printf("listen failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            this->isServerReady = false;
            return;
        }

    }

    /*
       Function : sendToClient()
       Arguments: char * data - the data that we want to send
       Purpose  : sends the given data to the client and returns
                  1 if we succesded or 0 if we failed.
    */
    virtual int  sendToClient(char* data, int size) = 0;

    /*
       Function : receive()
       Arguments: None.
       Purpose  : get data from client and returns the data,
                  if there was a problem fetching the data
                  the function will return nullptr
    */
    virtual void* receive() = 0;

    virtual int waitForNewClient() = 0;

    virtual int closeServer() = 0;
};

