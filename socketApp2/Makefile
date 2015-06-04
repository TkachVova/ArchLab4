CXXFLAGS  = -std=c++0x

simple_server_objects = ServerSocket.o Socket.o simple_server_main.o asioServer.o
simple_client_objects = ClientSocket.o Socket.o simple_client_main.o task.o task_resolver.o


all : simple_server simple_client tests

simple_server: $(simple_server_objects)
	g++ -pthread -o simple_server $(simple_server_objects) -lboost_serialization -lboost_program_options -lboost_system


simple_client: $(simple_client_objects)
	g++ -pthread -o simple_client $(simple_client_objects) -lboost_serialization -lboost_program_options -lboost_system

tests: 
	g++ tests.cpp -o Lab4Test -lpthread -std=c++11 -lboost_serialization -lboost_program_options -lboost_system -lboost_unit_test_framework


Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
ClientSocket: ClientSocket.cpp
simple_server_main: simple_server_main.cpp
simple_client_main: simple_client_main.cpp
task: task.cpp
asioServer: asioServer.cpp 
task_resolver: task_resolver.cpp
tests: tests.cpp 

clean:
	rm -f *.o simple_server simple_client
