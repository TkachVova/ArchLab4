#include "ClientSocket.h"
#include "SocketException.h"
#include "task.cpp"
#include <iostream>
#include <string>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum { max_length = 1024 };

int main ( int argc, char** argv )
{
	if(atoi(argv[2]) == 1) // if simple_client
	try
	{
		ClientSocket client_socket ( "localhost", 30000 );

		std::string reply;

		try
		{
			// in argv[3] we have data_len argument 
			std::cout << "argv" << atoi(argv[3]);
			task new_task(atoi(argv[3]));
			client_socket << new_task.save();
			client_socket >> reply;
		}
	  	catch ( SocketException& ) {}

	  	std::cout << "We received this response from the server:\n\"" << reply << "\"\n";;

	}
	catch ( SocketException& e )
	{
	  std::cout << "Exception was caught:" << e.description() << "\n";
	}
	
	if(atoi(argv[2]) == 2)
	 try
	  {
		/*if (argc != 3)
		{
		  std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
		  return 1;
		}*/

		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		tcp::resolver::query query(tcp::v4(), "127.0.0.1", "30000"); //argv[1], argv[2]);
		tcp::resolver::iterator iterator = resolver.resolve(query);

		tcp::socket s(io_service);
		boost::asio::connect(s, iterator);

		using namespace std; // For strlen.
		char request[atoi(argv[3])];//max_length];
		//std::cin.getline(request, max_length);
		task new_task(atoi(argv[3]));
		strcpy(request, new_task.save().c_str()); 
		size_t request_length = strlen(request);
		boost::asio::write(s, boost::asio::buffer(request, request_length));

		char reply[max_length];
		size_t reply_length = boost::asio::read(s,
		    boost::asio::buffer(reply, request_length));
		std::cout << "Reply is: ";
		std::cout << reply;
		std::cout << "\n";
	  }
	  catch (std::exception& e)
	  {
		std::cerr << "Exception: " << e.what() << "\n";
	  }	

	return 0;
}

