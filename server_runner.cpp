#include "server.hpp"

int main()
{
  Server *server = new Server();
  free(server);
  return 0;
}