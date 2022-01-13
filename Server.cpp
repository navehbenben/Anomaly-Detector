
#include "Server.h"
#include <unistd.h>
#include <sstream>


string SocketIO::read(){
	string serverInput="";
	char c=0;
	recv(clientID,&c,sizeof(char),0);
	while(c!='\n'){				
		serverInput+=c;
		recv(clientID,&c,sizeof(char),0);
	}
	return serverInput;


	// char input[200] = {0};
	// bzero(input,200);
	// recv(clientID, input, 200, 0);
	// string text = input;
	// text = text.substr(0,text.find('\0'));
	// return text;
}
void SocketIO::write(string text){
	send(clientID, text.c_str(), text.size(), 0);

}
void SocketIO::write(float f){
	string text;
	f = f*1000;
	f = f/1000;
	text = to_string(f);
	while (*(text.end()-1)=='0')
	{
		text = text.substr(0, text.size()-1);
	}

	write(text);
	

}
void SocketIO::read(float* f){
	bzero(f, sizeof(float));
	recv(clientID, f,sizeof(float),0);
}

Server::Server(int port)throw (const char*) {
	one = nullptr;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd<0)
	{
		throw "socket failed";
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);

	if (bind(fd,(struct sockaddr*)&server, sizeof(server))<0)
	{
		throw "fail in bind";
	}
	if (listen(fd, 2)<0)
	{
		throw "listen failed";
	}
	
	
}

void Server::start(ClientHandler& ch)throw(const char*){
	isOn = true;

	one = new thread([&ch, this] () {
		while (isOn){
		socklen_t clientSize = sizeof(client);
		int aClient = accept(fd,(struct sockaddr*)&client, &clientSize);
		if (aClient<0)
		{
			throw "failed connection";
		}
		ch.handle(aClient);
		close(aClient);

	}
		
	});
	
}

void Server::stop(){
	isOn = false;
	one->join(); // do not delete this!
	close(fd);
	
}

Server::~Server() {
}

