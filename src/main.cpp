#include <arpa/inet.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

const int BUFFER_SIZE = 1024;
const int PORT = 8080;
const std::string WEB_PAGES_PATH = "./webPages/";

std::string loadHtmlFile(const std::string &path)
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

int main()
{
  int server_fd, new_socket;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  char buffer[BUFFER_SIZE] = {0};

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    std::cerr << "Failed to create socket\n";
    return -1;
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);
  memset(address.sin_zero, '\0', sizeof(address.sin_zero));

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
  {
    std::cerr << "Failed to bind socket\n";
    return -1;
  }

  if (listen(server_fd, 3) < 0)
  {
    std::cerr << "Listen failed\n";
    return -1;
  }

  while (true)
  {
    std::cout << "Waiting for connection....\n";
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
      std::cerr << "Accept failed\n";
      return -1;
    }
    std::cout << "Connected with client at IP: " << inet_ntoa(address.sin_addr)
              << " and port: " << ntohs(address.sin_port) << "\n";

    read(new_socket, buffer, BUFFER_SIZE);
    std::cout << "Received from client: " << buffer << "\n";

    std::string response;
    std::istringstream request(buffer);
    std::string requestMethod;
    std::string requestUrl;
    request >> requestMethod >> requestUrl;

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
      htmlContent = loadHtmlFile(WEB_PAGES_PATH + "message.html");
    }
    else
    {
      htmlContent = loadHtmlFile(WEB_PAGES_PATH + "notfound.html");
    }

    if (htmlContent.empty())
    {
      htmlContent = "<h1>500 Internal Server Error</h1>";
      response = "HTTP/1.1 500 Internal Server Error\r\n"
                 "Content-Type: text/html\r\n"
                 "Connection: close\r\n\r\n" +
                 htmlContent;
    }
    else
    {
      response = "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/html\r\n"
                 "Connection: close\r\n\r\n" +
                 htmlContent;
    }

    send(new_socket, response.c_str(), response.size(), 0);
    close(new_socket);
  }

  close(server_fd);

  return 0;
}
