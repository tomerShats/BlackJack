#include "Server.h"
Server::Server(unsigned short port) :iServer(port)
{
}

int Server::sendToClient(char* data, int size)
{
    // Echo the buffer back to the sender
    iSendResult = send(ClientSocket, data, size, 0);
    if (iSendResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 0;
    }
    return 1;
}

void* Server::receive()
{
    memset(&recvbuf, 0, sizeof(recvbuf));
    iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
    if (iResult > 0)
    {
        return recvbuf;
    }
    else
    {
        std::cout << "Unable To Get data from client maybe reset the connection" << std::endl;
        return nullptr;
    }
}


int Server::waitForNewClient()
{
    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 0;
    }
    return 1;
}

int Server::closeServer()
{
    // No longer need server socket
    closesocket(ListenSocket);

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();
    return 1;
}


