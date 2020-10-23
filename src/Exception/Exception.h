#pragma once

#include <exception>
#include <string>

namespace IKEA::Exception {
  class Exception : public std::exception {
    public:
      Exception(std::string message) : m_Message(message) {}

      const char* what() const throw() {
        return m_Message.c_str();
      }

    protected:
      std::string m_Message;
  };
}
