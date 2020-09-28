#pragma once

#ifndef SERVER_HPP_
#define SERVER_HPP_

// Local
#include "connection_settings.hpp"

// System
#include <iostream>
#include <functional>

// Libs
#include <boost/asio.hpp>

using namespace std;
using namespace boost;

class Server
{
  public:
    Server();
    ~Server();
    void host();
};

#endif // SERVER_HPP_
