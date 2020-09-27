#pragma once

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "connection_settings.hpp"

#include <iostream>
#include <functional>
#include <boost/asio.hpp>

using namespace std;

class Server
{
  public:
    Server();
    ~Server();
    void host();
};

#endif // SERVER_HPP_
