#pragma once

#include <exception>
#include <string>

#include "Lineinfo.h"

#include "LIException.h"

namespace IKEA::Exception {
  class CircularImportException : public LIException {
    public:
      CircularImportException(std::string message, Lineinfo lineinfo)
        : LIException(message, lineinfo) {}
  };
}
