#ifndef MESSAGESERVICE_H
#define MESSAGESERVICE_H

#include <string>
#include <vector>

class MessageService
{
public:
  MessageService();
  ~MessageService();

  void addMessage(const std::string &message);
  std::vector<std::string> getMessages() const;
  std::string getLastMessage() const;

private:
  std::vector<std::string> messages;
};

#endif
