#pragma once

#include <exception>
#include <string>

#include "Lineinfo.h"

#include "Exception.h"

namespace IKEA::Exception {
  class FileImportException : public Exception {
    public:
      FileImportException(std::string message)
        : Exception(message) {}
  };
}
