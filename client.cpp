#include "client.hpp"

static boost::mutex d_mutex;

// Mutex para sec. crítica
Client::Client(
  asio::io_service service,
  string &server,
  string &path
) : 
  resolver(service),
  socket(service)
{
  size_t pos = server.find(':'); // Ponto de separação do "HOST":"PORT"

  if (pos == string::npos) return;

  string
    PORT = server.substr(pos+1),
    HOST = server.substr(0, pos);

  // Abre o file
  source.open(path, ios_base::binary|ios_base::ate);

  if (!source)
  {
    boost::mutex::scoped_lock lock(d_mutex);
    cout 
      << "\n\n"
      << __LINE__
      << "Erro ao ler/abrir arquivo: "
      << path
      << "\n\n"
    << endl;

    return;
  }

  size_t f_size = source.tellg(); // Read pos
  source.seekg(0); // Põe a read pos para o início do FDesc
  ostream req_stream(&req);

  req_stream << path << "---> " << f_size << "\n\n";
  
  {
    boost::mutex::scoped_lock lock(d_mutex);
    cout
      << "Tamanho do arquivo enviado --> "
      << req.size()
    << endl;
  }

  Resolver::query query_data(HOST, PORT);
  // TODO: WIP
  // resolver.async_resolve(
  //   query_data,
  //   boost::bind()
  // );
}

void Client::error_callback(
  const system::error_code &err,
  string cause = "Erro: "
)
{
  boost::mutex::scoped_lock lock(d_mutex);
  cout 
    << cause
    << err.message()
    << "\n\n"
  << endl;
}

void Client::file_controller(const system::error_code &err)
{
  if (err) error_callback(err);
  else
  {
    if (!source) return;
    else // || source.eof() == false)
    {
      source.read(
        buffer.c_array(), 
        (streamsize)buffer.size()
      );

      if (source.gcount() <= 0)
      {
        boost::mutex::scoped_lock lock(d_mutex);
        cout 
          << "Error: Ao ler arquivo (Num chars inválido)" 
        << endl;
        return;
      }

      {
        boost::mutex::scoped_lock lock(d_mutex);
        cout 
          << "ENVIADO " 
          << source.gcount() << "bytes\n"
          << "TOTAL " 
          << source.tellg() << " bytes\n"
          << "\n\n"
        << endl;
      }

      asio::async_write(
        socket,
        asio::buffer(
          buffer.c_array(),
          source.gcount()
        ),
        boost::bind(
          &Client::file_controller,
          this,
          asio::placeholders::error
        )
      );
    }
  }
}

void Client::connection_controller(
  const system::error_code &err, 
  Resolver::iterator end_iterator
)
{
  if (!err)
  {
    asio::async_write(
      socket,
      req,
      boost::bind(
        &Client::file_controller,
        this, 
        asio::placeholders::error
      )
    );
  }
  else if (end_iterator != Resolver::iterator())
  {
    socket.close();
    TCP::endpoint endpoint = *end_iterator;
    socket.async_connect(
      endpoint,
      boost::bind(
        &Client::connection_controller,
        this,
        asio::placeholders::error,
        ++end_iterator
      )
    );
  }
  else error_callback(err);
}

void Client::resolver_controller(
  const system::error_code &err, 
  Resolver::iterator end_iterator
)
{
  if (err) error_callback(err);
  else
  {
    TCP::endpoint endpoint = *end_iterator;
    socket.async_connect(
      endpoint,
      boost::bind(
        &Client::connection_controller,
        this,
        boost::asio::placeholders::error,
        ++end_iterator
      )
    );
  }
  // TODO: Connection controller
}