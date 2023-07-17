#include "message_service.h"

MessageService::MessageService() {}

MessageService::~MessageService() {}

void MessageService::addMessage(const std::string &message)
{
  messages.push_back(message);
}

std::vector<std::string> MessageService::getMessages() const
{
  return messages;
}

std::string MessageService::getLastMessage() const
{
  if (!messages.empty())
  {
    return messages.back();
  }
  return "";
}