#include "request_handler.h"
#include <arpa/inet.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

const int BUFFER_SIZE = 8192;
const std::string WEB_PAGES_PATH = "./web/";

RequestHandler::RequestHandler(int new_socket, MessageService &messageService)
    : new_socket(new_socket), messageService(messageService) {}

RequestHandler::~RequestHandler()
{
  close(new_socket);
}

void RequestHandler::handleRequest()
{
  char buffer[BUFFER_SIZE] = {0};
  int valread = read(new_socket, buffer, BUFFER_SIZE);
  std::cout << "Received from client: " << buffer << "\n";
  std::istringstream request(buffer);
  std::string requestMethod;
  std::string requestUrl;
  request >> requestMethod >> requestUrl;
  std::string postData = parsePostData(buffer, valread);
  std::string response = generateResponse(requestUrl, postData);
  sendResponse(response);
}

std::string RequestHandler::parsePostData(char buffer[], int valread)
{
  std::string data = std::string(buffer);
  std::string postData;
  size_t findContentLength = data.find("Content-Length: ");
  if (findContentLength != std::string::npos)
  {
    size_t endOfContentLengthString = data.find("\r\n", findContentLength);
    if (endOfContentLengthString == std::string::npos)
    {
      std::cerr << "Malformed request, can't find the end of Content-Length header.\n";
      return postData;
    }

    std::string contentLengthStr = data.substr(findContentLength + 16, endOfContentLengthString - (findContentLength + 16));
    int contentLength;
    try
    {
      contentLength = std::stoi(contentLengthStr);
    }
    catch (const std::exception &e)
    {
      std::cerr << "Malformed request, can't parse Content-Length value: " << contentLengthStr << "\n";
      return postData;
    }

    std::string headerEnd("\r\n\r\n");
    size_t headersEnd = data.find(headerEnd);
    if (headersEnd != std::string::npos)
    {
      headersEnd += headerEnd.size();
      size_t bodyLength = data.size() - headersEnd;
      if (bodyLength < contentLength)
      {
        char bodyBuffer[BUFFER_SIZE] = {0};
        size_t toRead = contentLength - bodyLength;
        size_t totalRead = 0;
        while (totalRead < toRead)
        {
          int bytesRead = read(new_socket, bodyBuffer + totalRead, toRead - totalRead);
          if (bytesRead <= 0)
          {
            std::cerr << "Failed to read POST body\n";
            break;
          }
          totalRead += bytesRead;
        }
        postData = data.substr(headersEnd) + std::string(bodyBuffer, totalRead);
      }
      else
      {
        if (contentLength > data.size())
        {
          std::cerr << "Content length is greater than the data size.\n";
          return postData;
        }
        postData = data.substr(headersEnd, contentLength);
      }
    }
  }
  return postData;
}

std::string RequestHandler::generateResponse(std::string requestUrl, std::string postData)
{
  std::string htmlContent;
  if (requestUrl == "/")
  {
    htmlContent = loadHtmlFile(WEB_PAGES_PATH + "index.html");
  }
  else if (requestUrl == "/home")
  {
    htmlContent = loadHtmlFile(WEB_PAGES_PATH + "home.html");
  }
  else if (requestUrl == "/message")
  {
    if (!postData.empty())
    {
      size_t prefixLength = std::string("user_message=").length();
      if (postData.length() > prefixLength)
      {
        std::string message = postData.substr(prefixLength);
        messageService.addMessage(message);
        htmlContent = loadHtmlFile(WEB_PAGES_PATH + "message.html");

        size_t pos = htmlContent.find("{{message}}");
        if (pos != std::string::npos)
        {
          htmlContent.replace(pos, 11, message);
        }
        else
        {
          std::cerr << "Failed to find {{message}} placeholder in the HTML content.\n";
        }
      }
    }
    else
    {
      htmlContent = loadHtmlFile(WEB_PAGES_PATH + "home.html");
    }
  }
  else
  {
    htmlContent = loadHtmlFile(WEB_PAGES_PATH + "notfound.html");
  }

  if (htmlContent.empty())
  {
    htmlContent = "<h1>500 Internal Server Error</h1>";
    return "HTTP/1.1 500 Internal Server Error\r\n"
           "Content-Type: text/html\r\n"
           "Connection: close\r\n\r\n" +
           htmlContent;
  }
  else
  {
    return "HTTP/1.1 200 OK\r\n"
           "Content-Type: text/html\r\n"
           "Connection: close\r\n\r\n" +
           htmlContent;
  }
}

void RequestHandler::sendResponse(std::string response)
{
  send(new_socket, response.c_str(), response.size(), 0);
}

std::string RequestHandler::loadHtmlFile(const std::string &path)
{
  std::ifstream file(path);
  if (file)
  {
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
  }
  else
  {
    std::cerr << "Failed to open file at: " << path << "\n";
    return "";
  }
}
