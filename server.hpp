#pragma once

#ifndef SERVER_HPP_
#define SERVER_HPP_

// Local
#include "connection_settings.hpp"

class Server : boost::enable_shared_from_this<Server>
{
  public:
    void create(unsigned short port);
  private:
    Server() {};
    ~Server() {};
};

#endif // SERVER_HPP_
