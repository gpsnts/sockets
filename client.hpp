#pragma once

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "connection_settings.hpp"

#include <iostream>

using namespace std;

class Client
{
  public:
    Client();
    ~Client();
    void connect();
};

#endif // CLIENT_HPP_