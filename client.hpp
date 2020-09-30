#pragma once

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

// Local
#include "connection_settings.hpp"

class Client : boost::enable_shared_from_this<Client>
{
  public:
    Client();
};

#endif // CLIENT_HPP_