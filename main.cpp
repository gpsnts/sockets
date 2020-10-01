// Isto é para rodar o Server/Cliente local. Os "logs" aparecem no console

#include "connector.hpp"
#include "server.hpp"
#include "client.hpp"

#define PORT 1337

static boost::mutex l_mutex;

void receiver(void)
{
  try
  {
    {
      boost::mutex::scoped_lock lock(l_mutex);
      cout 
        << "--- Recebendo dados ---"
        << "\n\n";
    }

    Server tcp_server(PORT); // Usando a porta 1337
  }
  catch(std::exception const &err)
  {
    cerr
      << "ERROR:: "
      << err.what()
      << "\n\n";
  }
}

void sender(
  string const &filename,
  string const &address = "localhost:1337"
)
{
  try
  {
    asio::io_service service;

    {
      boost::mutex::scoped_lock lock(l_mutex);
      cout 
        << "Endereço (host:port) -- " 
        << address 
        << "\n" 
        << "Arquivo enviado"
        << filename 
        << '\n\n';
    }

    Client client(
      service,
      address,
      filename
    );

    service.run();
  }
  catch (std::exception const &err)
  {
    cerr
      << "ERROR:: "
      << err.what()
      << "\n\n";
  }
}


// Isso é para rodar o Server/Cliente localmente a fim de demonstrar/exemplificar
int main()
{
    boost::thread_group group;
    group.create_thread(receiver); // Listener para "escutar"
    boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
    group.create_thread([] { sender("./exemplo.txt"); });
    group.join_all();
}
