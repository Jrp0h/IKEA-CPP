#pragma once

#include <exception>
#include <string>

#include "Lineinfo.h"
#include "ProgramFiles.h"

#include "LIException.h"

namespace IKEA::Exception {
  class InvalidArgumentCountException : public LIException {
    public:
      InvalidArgumentCountException(std::string message, Lineinfo lineinfo) 
        : LIException(message, lineinfo) {}
  };
}
