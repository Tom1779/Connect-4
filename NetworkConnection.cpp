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

void NetworkConnection::init_client()
{
	string server_address_string;
	cout << "Please enter server address: ";
	getline(cin, server_address_string);
	server_address = IpAddress(server_address_string);
}

void NetworkConnection::init_server()
{
	server_address = IpAddress::getLocalAddress();
	cout << "Please connect the client to this address: " << server_address.toString() << endl;
}
