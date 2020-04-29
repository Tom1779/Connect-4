#ifndef NETWORKCONNECTION_H
#define NETWORKCONNECTION_H

#include <iostream>
#include <algorithm>
#include <SFML\Network\IpAddress.hpp>

using namespace sf;
using namespace std;

class NetworkConnection
{
public:

	NetworkConnection();
	~NetworkConnection();
	void init();

private:

	IpAddress server_address;
	bool is_server;
	int server_tcp_port;

	void init_client();
	void init_server();
};

#endif