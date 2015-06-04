#include "ServerSocket.h"
#include "SocketException.h"
#include "task.cpp"
#include <string>
#include <iostream>
#include <unistd.h>
#include <vector>
#include "asioServer.cpp"
#include "task_resolver.cpp"

#include <cstdlib> 
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#define THREADING_FORK 1
#define THREADING_PTHREAD 2
#define ASIO_ASYNC 3

#ifndef SERVER_MODEL
#define SERVER_MODEL ASIO_ASYNC
#endif

using namespace std;

ServerSocket new_sock;

void doprocessing (ServerSocket sock)
{
	try
	{
		//while ( true )
		//{
			std::cout << "inside doprocessing: " << "\n";
			std::string data;
			sock >> data;
			task new_task;
			new_task.load(data);
			std::cout << "\n";
			std::cout << "new_task number: " << new_task.number << "\n";
			std::cout << "new_task text: " << new_task.text << "\n";
			sock << resolver::FindPalindroms(new_task.text, new_task.number); // send reply
		//}
	}
	catch ( SocketException& ) {}
}


void *process_to_client(void* iter) {
	//long int iterator = (long int)iter;
	//std::cout << "process_to_client iterator: " << iterator << "\n";
	//std::cout << "process_to_client socket: " << sockets[iterator - 1] << "\n";
	//doprocessing(sockets[iterator - 1]);
	doprocessing(new_sock);
	return NULL;
}



int main ( int argc, char* argv[] )
{
	if (argc != 2)
    {
      std::cerr << "Enter argument 1..3\n";
      return 1;
    }
	
	int server_model = std::atoi(argv[1]);

	std::cout << "running....\n";
	
	if (server_model == THREADING_FORK || server_model == THREADING_PTHREAD)
	try
	{
		// Create the socket
		ServerSocket server_sock ( 30000 );
		
		while ( true )
		{
			//ServerSocket new_sock;
			server_sock.accept ( new_sock );
			//sockets.push_back(new_sock);			

			if (server_model == THREADING_FORK)
			{
				/* Create child process */
				int pid;
				pid = fork();
				if (pid < 0)
				{
					perror("ERROR on fork");
					exit(1);
				}

				if (pid == 0)
				{
					/* This is the client process */
					//close(server);
					doprocessing(new_sock);
					exit(0);
				}
				else
				{
					//close(new_sock);
				}
			}
			else if (server_model == THREADING_PTHREAD)
			{
				pthread_t pth;
				//long int size = (int)sockets.size();
				//std::cout << "main sockets size: " << size << "\n";
				//pthread_create(&pth, NULL, &process_to_client, (void*)size);
				pthread_create(&pth, NULL, &process_to_client, NULL);
			}

			//try
			//{
			//	while ( true )
			//	{
			//		std::string data;
			//		new_sock >> data;
			//		task new_task;
			//		new_task.load(data);
			//		std::cout << "\n";
			//		std::cout << "new_task number: " << new_task.number << "\n";
			//		std::cout << "new_task text: " << new_task.text << "\n";
			//		new_sock << FindPalindroms(new_task.text, new_task.number); // send reply
			//	}
			//}
	  		//catch ( SocketException& ) {}

		}
	}
	catch ( SocketException& e )
	{
	  std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
	}
	
	if (server_model == ASIO_ASYNC)
	{
		try
		{
			boost::asio::io_service io_service;
			server s(io_service, 30000);
			io_service.run();
		} 
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
		}
	}


	return 0;
}

