#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <string>
#include "message_service.h"

class RequestHandler
{
public:
  RequestHandler(int new_socket, MessageService &messageService);
  ~RequestHandler();
  void handleRequest();

private:
  int new_socket;
  MessageService &messageService;
  std::string parseRequest();
  std::string generateResponse(std::string requestUrl, std::string postData);
  void sendResponse(std::string response);
  std::string loadHtmlFile(const std::string &path);
  std::string parsePostData(char buffer[], int valread);
};

#endif
