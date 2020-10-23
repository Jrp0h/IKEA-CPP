#pragma once

#include <exception>
#include <string>

#include "Lineinfo.h"
#include "ProgramFiles.h"

#include "LIException.h"

namespace IKEA::Exception {
  class MemoryOutOfRangeException : public LIException {
    public:
      MemoryOutOfRangeException(std::string message, Lineinfo lineinfo) 
        : LIException(message, lineinfo) {}
  };
}
