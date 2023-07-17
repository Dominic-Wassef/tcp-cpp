#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include "request_handler.h"
#include "message_service.h"

class Server
{
public:
  Server(int port);
  ~Server();
  void start();

private:
  int server_fd;
  struct sockaddr_in address;
  MessageService messageService;

  int acceptConnection();
  void handleClient(int client_socket);
};

#endif
