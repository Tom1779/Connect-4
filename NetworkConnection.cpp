#include "NetworkConnection.h"

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

	is_server = (is_server_string == "YES");

	if (is_server)
	{
		init_server();
	}
	else
	{
		init_client();
	}
}

void NetworkConnection::send(int data)
{
	sf::Int16 sf_data = data;
	Packet packet;
	packet << sf_data;
	socket.send(packet);
	
}

int NetworkConnection::recieve()
{
	sf::Int16 sf_data;
	Packet packet;
	packet >> sf_data;
	socket.receive(packet);
	if (packet >> sf_data)
	{
		// cout << "packet read succesfully" << endl;
	}
	else
	{
		cout << "Failed to read packet" << endl;
		system("pause");
		exit(1);
	}
	return sf_data;
}

void NetworkConnection::init_server()
{
	Int16 message;
	server_address = IpAddress::getLocalAddress();
	cout << "Please connect the client to this address: " << server_address.toString() << endl;
	if (server_listener.listen(server_tcp_port) != Socket::Done)
	{
		cout << "Error: Server Failed To Bind Socket" << endl;
		exit(1);
	}
	cout << "listening succeded" << endl;
	if (server_listener.accept(socket) != Socket::Done)
	{
		cout << "Server Failed To Accept Connection" << endl;
		exit(1);
	}
	cout << "Server Succesfully Accepted Connection" << endl;
	message = recieve();
	cout << "The message is: " << message << endl;
}

void NetworkConnection::init_client()
{
	INT16 message = 3;
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
	Packet packet;
	packet << message;
	socket.send(packet);
	send(message);
}

