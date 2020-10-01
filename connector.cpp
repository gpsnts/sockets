#include "connector.hpp"

static boost::mutex d_mutex; // Sec. crítica

Connector::Connector(
  asio::io_service &service
) :
  _socket(service),
  f_size(0) {}

void Connector::request_reader_controller(
  const system::error_code &err,
  size_t transferred_bytes
)
{
  istream req_stream(&req_buffer);
  string path;

  req_stream >> path;
  req_stream >> f_size;
  req_stream.read(buffer.c_array(), 2);

  size_t pos = path.find_last_of('\\');
  
  if (pos != string::npos)
  {
    path = path.substr(pos + 1);
  }

  output.open(
    path + " - RECEBIDO",
    ios_base::binary
  );

  if (!output) return;

  // ""Flush"" do arquivo
  do
  {
    req_stream.read(
      buffer.c_array(), (streamsize)buffer.size()
    );

    output.write(
      buffer.c_array(),
      req_stream.gcount()
    );
  } while (req_stream.gcount() > 0);

  // asio::async_read_until
  asio::async_read(
    socket,
    asio::buffer(
      buffer.c_array(),
      buffer.size()
    ),
    boost::bind(
      &Connector::file_content_reader_controller,
      shared_from_this(),
      asio::placeholders::error,
      asio::placeholders::bytes_transferred
    )
  );
}

void Connector::file_content_reader_controller(
  system::error_code &err,
  size_t transferred_bytes
)
{
  if (transferred_bytes > 0)
  {
    output.write(
      buffer.c_array(),
      (streamsize)transferred_bytes
    );

    if (output.tellp() >= (streamsize)f_size) return;
  }

  asio::async_read(
    socket, 
    boost::asio::buffer(
      buffer.c_array(), 
      buffer.size()
    ), 
    boost::bind(
      &Connector::file_content_reader_controller, 
      shared_from_this(), 
      asio::placeholders::error, 
      asio::placeholders::bytes_transferred
    )
  );
}