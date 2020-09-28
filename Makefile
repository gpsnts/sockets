CC=g++
CXXFLAGS=-Wall -Wextra -pedantic -pthread
LDLIBS=-lboost_system -lpthread

build: client_runner.cpp client.cpp client.hpp server_runner.cpp server.cpp server.hpp
	$(CC) client_runner.cpp client.cpp -o client $(CXXFLAGS) $(LDLIBS)
	$(CC) server_runner.cpp server.cpp -o server $(CXXFLAGS) $(LDLIBS)

clean: client server
	rm -rf client server

client: client_runner.cpp client.cpp client.hpp
	$(CC) client_runner.cpp client.cpp -o client $(CXXFLAGS) $(LDLIBS)

server: server_runner.cpp server.cpp server.hpp
	$(CC) server_runner.cpp server.cpp -o server $(CXXFLAGS) $(LDLIBS)
