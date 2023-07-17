#include "server.h"
#include <iostream>

const int PORT = 8080;

int main()
{
  Server server(PORT);

  std::cout << "Server started at port " << PORT << "\n";
  server.start();

  return 0;
}
