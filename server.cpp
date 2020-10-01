#include "server.hpp"

// Destructor
Server::~Server()
{
  service.stop();
}

Server::Server(unsigned short port)
: acceptor(
    service,
    TCP::endpoint(
      TCP::v4(), // IPv4
      port
    ),
    true
  )
{
  ptr_server_tcp_connection connection(new Connector(service));
  acceptor.async_accept(
    connection->getConnectorSocket(),
    boost::bind(
      &Server::accept_controller,
      this,
      connection,
      asio::placeholders::error
    )
  );
}

void Server::accept_controller(
  ptr_server_tcp_connection connection,
  system::error_code &err
)
{
  if (!err) connection->start_connector();
}