#pragma once

#ifndef CONNECTOR_HPP_
#define CONNECTOR_HPP_

// Local
#include "connection_settings.hpp"

class Connector : boost::enable_shared_from_this<Connector>
{
  public:
    asio::streambuf req_buffer;
    ofstream output;
    Socket _socket;
    size_t f_size;
    boost::array<char, 51200> buffer;

    Connector(asio::io_service &service);

    Socket& getConnectorSocket() 
    { 
      return _socket;
    }
    
    void start_connector()
    {
      asio::async_read_until(
        _socket,
        req_buffer,
        "\n\n\n",
        boost::bind(
          &Connector::request_reader_controller,
          shared_from_this(),
          asio::placeholders::error,
          asio::placeholders::bytes_transferred
        )
      );
    };
  
  private:
    void request_reader_controller(
      const system::error_code &err,
      size_t transferred_bytes
    );

    void file_content_reader_controller(
      system::error_code &err,
      size_t transferred_bytes
    );
};

#endif // CONNECTOR_HPP_