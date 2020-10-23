#pragma once

#include <string>

#include "Str.h"
#include "Lineinfo.h"
#include "Memory/Register.h"
#include "ProgramFiles.h"

#include "Exception/MemoryOutOfRangeException.h"
#include "Exception/NotANumberException.h"

using namespace IKEA::Memory;
using namespace IKEA::Exception;

namespace IKEA {
  enum class ValueType { VAR, VAR_VALUE, DIRECT, PLAIN };

  class ValueParser {
  public:
    static int GetMemoryLocationFromVar(std::string arg) {

      Str::Trim(arg);

      if(arg.find("&") == 0 || arg.find("$") == 0)
        arg = arg.erase(0, 1);
      
      return Register::GetVar(arg).GetValue();
    }

    static ValueType Parse(std::string arg, int& value, Lineinfo lineinfo, bool asPlain = false, bool string = false)
    {
      Str::Trim(arg);

      if(arg.find("&") == 0)
      {
        arg = arg.erase(0, 1);
        value = Register::GetVar(arg).GetValue();
        return ValueType::VAR;
      }
      else if(arg.find("$") == 0)
      {
        arg = arg.erase(0, 1);
        value = Register::GetVar(arg).GetValue();

        if(value >= 32)
          throw MemoryOutOfRangeException(arg + " is not a valid memory address. 0-31 is valid.", lineinfo);

        value = Register::GetMemoryAt(value).GetValue();
        return ValueType::VAR_VALUE;
      }
      else if(arg.find("#") == 0)
      {
        arg = arg.erase(0, 1);
        try {
          value = std::stoi(arg);

          if(value >= 32)
            throw MemoryOutOfRangeException(arg + " is not a valid memory address. 0-31 is valid.", lineinfo);

          if(asPlain)
            return ValueType::DIRECT;

          value = Register::GetMemoryAt(value).GetValue();
          return ValueType::DIRECT;
        }
        catch(const std::exception& e)
        {
          throw MemoryOutOfRangeException(arg + " is not a valid memory address. 0-31 is valid.", lineinfo);
        }
      }
      else {
        try {
          if(string)
          {
            value = 0;
            return ValueType::PLAIN;
          }
          value = std::stoi(arg);
          return ValueType::PLAIN;
        }
        catch(const std::exception& e)
        {
          std::cout << e.what() << std::endl;
          throw NotANumberException(arg + " is not a valid number.", lineinfo);
        }
      }
    }
  };
}
