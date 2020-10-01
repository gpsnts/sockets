#pragma once

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

// Local
#include "connection_settings.hpp"

class Client : boost::enable_shared_from_this<Client>
{
  public:
    Client(
      asio::io_service &service,
      const string &server,
      const string &path
    );

    TCP::resolver resolver;
    Socket socket;
    boost::array<char, 1024> buffer;
    asio::streambuf req;
    ifstream source;
  
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