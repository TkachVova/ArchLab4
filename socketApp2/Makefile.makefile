CXXFLAGS  = -std=c++0x

server_objects = server.o 
client_objects = client.o


all : server client

server: $(server_objects)
	g++ -pthread -o server $(server_objects) -lboost_serialization -lboost_program_options -lboost_system


client: $(client_objects)
	g++ -pthread -o client $(client_objects) -lboost_serialization -lboost_program_options -lboost_system

server: server.cpp
client: client.cpp
 

clean:
	rm -f *.o simple_server simple_client
