#pragma once
#include "iServer.h"
class Server :
	public iServer
{
public:
	Server(unsigned short port);
	virtual int   sendToClient(char* data, int size);
	virtual void* receive();
	virtual int waitForNewClient();
	virtual int closeServer();
};

