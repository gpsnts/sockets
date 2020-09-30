#pragma once

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

// Local
#include "connection_settings.hpp"

class Client : boost::enable_shared_from_this<Client>
{
  public:
    TCP::resolver resolver;
    Socket socket;
    boost::array<char, 1024> buffer;
    asio::streambuf req;
    ifstream source;

    Client(
      asio::io_service service,
      string &server,
      string &path
    );
  
  private:
    void file_controller(
      const system::error_code &err
    );
    
    void connection_controller(
      const system::error_code &err,
      Resolver::iterator end_iterator
    );

    void resolver_controller(
      const system::error_code &err, 
      Resolver::iterator end_iterator
    );

    void error_callback(
      const system::error_code &err,
      string cause = "Erro: "
    );
};

#endif // CLIENT_HPP_