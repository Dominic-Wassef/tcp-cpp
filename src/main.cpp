#include <arpa/inet.h> // For sockaddr_in and inet_ntoa
#include <cstring>     // For memset
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sstream> // For parsing HTTP request
#include <sys/socket.h>
#include <unistd.h> // For close

const int BUFFER_SIZE = 1024;
const int PORT = 4000;

int main()
{
  int server_fd, new_socket;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  char buffer[BUFFER_SIZE] = {0};

  // Creating socket
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    std::cerr << "Failed to create socket\n";
    return -1;
  }

  // Configure server address structure
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  memset(address.sin_zero, '\0', sizeof(address.sin_zero));

  // Bind the socket
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
  {
    std::cerr << "Failed to bind socket\n";
    return -1;
  }

  // Listen for connections
  if (listen(server_fd, 3) < 0)
  {
    std::cerr << "Listen failed\n";
    return -1;
  }

  while (true)
  {
    std::cout << "Waiting for connection....\n";

    // Accept a connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0)
    {
      std::cerr << "Accept failed\n";
      return -1;
    }

    std::cout << "Connected with client at IP: " << inet_ntoa(address.sin_addr)
              << " and port: " << ntohs(address.sin_port) << "\n";

    // Read from the socket
    recv(new_socket, buffer, BUFFER_SIZE, 0);
    std::cout << "Received from client: " << buffer << "\n";

    // Parse the request and generate a response
    std::string response;
    std::istringstream request(buffer);
    std::string requestMethod;
    std::string requestUrl;

    // Parse the request line
    request >> requestMethod >> requestUrl;

    if (requestUrl == "/")
    {
      // Respond with a page that has a button linking to /home
      response = "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/html\r\n"
                 "Connection: close\r\n\r\n"
                 "<!DOCTYPE html>\n"
                 "<html>\n"
                 "<body>\n"
                 "<button onclick=\"location.href='/home'\" type=\"button\">\n"
                 "Go to the next page\n"
                 "</button>\n"
                 "</body>\n"
                 "</html>\n";
    }
    else if (requestUrl == "/home")
    {
      // Respond with a different page
      response = "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/html\r\n"
                 "Connection: close\r\n\r\n"
                 "<!DOCTYPE html>\n"
                 "<html>\n"
                 "<body>\n"
                 "<h1>This is the next page</h1>\n"
                 "</body>\n"
                 "</html>\n";
    }
    else
    {
      // For any other URL, respond with a 404 not found status
      response = "HTTP/1.1 404 Not Found\r\n"
                 "Content-Type: text/html\r\n"
                 "Connection: close\r\n\r\n"
                 "<!DOCTYPE html>\n"
                 "<html>\n"
                 "<body>\n"
                 "<h1>Page not found</h1>\n"
                 "</body>\n"
                 "</html>\n";
    }

    std::cout << "RequestMethod: " << requestMethod << "\n";
    std::cout << "RequestUrl: " << requestUrl << "\n";

    // Send the response to the client
    send(new_socket, response.c_str(), response.size(), 0);

    // Close the new socket
    close(new_socket);
  }

  // Close the server socket
  close(server_fd);

  return 0;
}
