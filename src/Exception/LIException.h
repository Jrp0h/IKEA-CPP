#pragma once

#include <exception>
#include <string>

#include "Lineinfo.h"
#include "ProgramFiles.h"

namespace IKEA::Exception {
  class LIException : public std::exception {
    public:
      LIException(std::string message, Lineinfo lineinfo){ 
        m_FullMessage = message + " " + ProgramFiles::LineinfoToString(lineinfo);
      }

      const char* what() const throw() {
        return m_FullMessage.c_str();
      }

    protected:
      std::string m_FullMessage;
  };
}
