#pragma once

#include <exception>
#include <string>

#include "Lineinfo.h"
#include "ProgramFiles.h"

#include "LIException.h"

namespace IKEA::Exception {
  class InvalidSyntaxException : public LIException {
    public:
      InvalidSyntaxException(std::string message, Lineinfo lineinfo) 
        : LIException(message, lineinfo) {}
  };
}
