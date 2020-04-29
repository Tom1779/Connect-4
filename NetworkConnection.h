#ifndef NETWORKCONNECTION_H
#define NETWORKCONNECTION_H

#include <iostream>
#include <algorithm>
#include <SFML\Network.hpp>

using namespace sf;
using namespace std;

class NetworkConnection
{
public:

	NetworkConnection();
	~NetworkConnection();

	void init();
	void send(int data);
	int recieve();

private:

	IpAddress server_address;
	bool is_server;
	int server_tcp_port;
	TcpListener server_listener;
	TcpSocket socket;

	void init_server();
	void init_client();
};

#endif