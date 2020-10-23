#pragma once

#include <exception>
#include <string>

#include "Lineinfo.h"
#include "ProgramFiles.h"

#include "LIException.h"

namespace IKEA::Exception {
  class UndefinedLocationException : public LIException {
    public:
      UndefinedLocationException(std::string message, Lineinfo lineinfo) 
        : LIException(message, lineinfo) {}
  };
}
