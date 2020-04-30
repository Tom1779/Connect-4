#include "NetworkConnection.h"

sf::Packet& operator <<(sf::Packet& packet, const UserData& data)
{
	return packet << data.col << data.user_name;
}

sf::Packet& operator >>(sf::Packet& packet, UserData& data)
{
	return packet >> data.col >> data.user_name;
}

NetworkConnection::NetworkConnection()
{
	server_tcp_port = 3000;
}

NetworkConnection::~NetworkConnection()
{
}

void NetworkConnection::init()
{
	string is_server_string;
	do
	{
		cout << "Is this computer the server(yes/no): ";
		getline(cin, is_server_string);
		for_each(is_server_string.begin(), is_server_string.end(), [](char& c)
			{
				c = ::toupper(c);
			});
	} while (is_server_string != "YES" && is_server_string != "NO");

	_is_server = (is_server_string == "YES");

	if (_is_server)
	{
		init_server();
	}
	else
	{
		init_client();
	}
}

void NetworkConnection::send(UserData data)
{
	Packet packet;
	packet << data;
	socket.send(packet);
}

UserData NetworkConnection::recieve()
{
	UserData data;
	Packet packet;
	socket.receive(packet);
	if (packet >> data)
	{
		// cout << "packet read succesfully" << endl;
	}
	else
	{
		cout << "Failed to read packet" << endl;
		system("pause");
		exit(1);
	}
	return data;
}

bool NetworkConnection::is_server()
{
	return _is_server;
}

void NetworkConnection::init_server()
{
	server_address = IpAddress::getLocalAddress();
	cout << "Please connect the client to this address: " << server_address.toString() << endl;
	if (server_listener.listen(server_tcp_port) != Socket::Done)
	{
		cout << "Error: Server Failed To Bind Socket" << endl;
		exit(1);
	}
	cout << "Waiting for client to connect..." << endl;
	if (server_listener.accept(socket) != Socket::Done)
	{
		cout << "Server Failed To Accept Connection" << endl;
		exit(1);
	}
	cout << "Server Succesfully Accepted Connection" << endl;
}

void NetworkConnection::init_client()
{
	string server_address_string;
	cout << "Please enter server address: ";
	getline(cin, server_address_string);
	server_address = IpAddress(server_address_string);
	Socket::Status status = socket.connect(server_address, server_tcp_port);
	if (status != Socket::Done)
	{
		cout << "Client Failed To Connect" << endl;
		exit(1);
	}
	cout << "Client connected succesfully" << endl;
}

