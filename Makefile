CC=g++
CXXFLAGS=-Wall -Wextra -pedantic -pthread
LDLIBS=-lboost_system -lboost_thread -lpthread

build: client.cpp server.cpp connector.cpp main.cpp
	$(CC) main client.cpp server.cpp connector.cpp -o app $(CXXFLAGS) $(LDLIBS)

clean: app
	rm -rf app