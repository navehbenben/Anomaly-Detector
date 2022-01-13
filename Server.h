/*
 * Server.h
 *
 *  Created on: Dec 13, 2020
 *      Author: Eli
 */

#ifndef SERVER_H_
#define SERVER_H_
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "CLI.h"

using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
    public:
    virtual void handle(int clientID)=0;
};


// you can add helper classes here and implement on the cpp file
class SocketIO: public DefaultIO{
	int clientID;
	char * IN;
	public:
	SocketIO(int id){
		clientID = id;
	}
	virtual string read();
	virtual void write(string text);
	virtual void write(float f);
	virtual void read(float* f);

};

// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
	public:
    virtual void handle(int clientID){
		SocketIO dio = SocketIO(clientID);
		CLI cli = CLI(&dio);
		cli.start();

    }
};


// implement on Server.cpp
class Server {
	thread* one; // the thread to run the start() method in
	bool isOn;

	// you may add data members
	int fd;
	sockaddr_in server;
	sockaddr_in client;

public:
	Server(int port) throw (const char*);
	virtual ~Server();
	void start(ClientHandler& ch)throw(const char*);
	void stop();
};

#endif /* SERVER_H_ */
