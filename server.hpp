#pragma once

#ifndef SERVER_HPP_
#define SERVER_HPP_

// Lib
#include <boost/noncopyable.hpp>

// Local
#include "connection_settings.hpp"
#include "connector.hpp"

class Server : private boost::noncopyable
{
  public:
    typedef boost::shared_ptr<Connector> ptr_server_tcp_connection;
    asio::io_service service;
    TCP::acceptor acceptor;

    Server(unsigned short port);
    ~Server();
    
    void accept_controller(
      ptr_server_tcp_connection connection,
      system::error_code &err
    );
};

#endif // SERVER_HPP_
