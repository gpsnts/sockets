CC=clang++
CXXFLAGS= -pedantic -pthread
LDLIBS=-lboost_system -lboost_thread

build: client.cpp server.cpp connector.cpp main.cpp
	$(CC) -std=c++11 -g -O0 client.cpp server.cpp connector.cpp -o app $(CXXFLAGS) $(LDLIBS)

clean: app
	rm -rf app

run: app
	./app
