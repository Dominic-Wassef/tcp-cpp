#include "server.h"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

Server::Server(int port)
{
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    std::cerr << "Failed to create socket\n";
    exit(-1);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  memset(address.sin_zero, '\0', sizeof(address.sin_zero));

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
  {
    std::cerr << "Failed to bind socket\n";
    exit(-1);
  }

  if (listen(server_fd, 3) < 0)
  {
    std::cerr << "Listen failed\n";
    exit(-1);
  }
}

Server::~Server()
{
  close(server_fd);
}

void Server::start()
{
  while (true)
  {
    int client_socket = acceptConnection();
    if (client_socket != -1)
    {
      handleClient(client_socket);
    }
  }
}

int Server::acceptConnection()
{
  int addrlen = sizeof(address);
  int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
  if (new_socket < 0)
  {
    std::cerr << "Accept failed\n";
  }
  return new_socket;
}

void Server::handleClient(int client_socket)
{
  RequestHandler requestHandler(client_socket, messageService);
  requestHandler.handleRequest();
}
