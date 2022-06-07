#ifndef NETWORKCONNECTION_H
#define NETWORKCONNECTION_H

#include <iostream>
#include <algorithm>
#include <SFML\Network.hpp>

using namespace sf;
using namespace std;

struct UserData
{
	Int16 col;
	sf::String user_name;
};
sf::Packet& operator <<(sf::Packet& packet, const UserData& data);
sf::Packet& operator >>(sf::Packet& packet, UserData& data);


class NetworkConnection
{
public:

	NetworkConnection();
	~NetworkConnection();

	void init();
	void send(UserData);
	UserData recieve();
	bool is_server();
	TcpSocket socket;

private:

	IpAddress server_address;
	bool _is_server;
	int server_tcp_port;
	TcpListener server_listener;


	void init_server();
	void init_client();
};

#endif