#include "client.hpp"

int main()
{
  Client *client = new Client();
  free(client);

  return 0;
}