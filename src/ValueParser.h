#pragma once

#include <string>

#include "Str.h"
#include "Lineinfo.h"
#include "Memory/Register.h"
#include "ProgramFiles.h"

using namespace IKEA::Memory;

namespace IKEA {
  enum class ValueType { VAR, VAR_VALUE, DIRECT, PLAIN };

  class ValueParser {
  public:
    static ValueType Parse(std::string arg, int& value, Lineinfo lineinfo, bool asPlain = false)
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
          throw std::runtime_error(arg + " is not a valid memory address. 0 - 31 is valid. " + ProgramFiles::LineinfoToString(lineinfo));

        value = Register::GetMemoryAt(value).GetValue();
        return ValueType::VAR_VALUE;
      }
      else if(arg.find("#") == 0)
      {
        arg = arg.erase(0, 1);
        try {
          value = std::stoi(arg);

          if(asPlain)
            return ValueType::DIRECT;

          value = Register::GetMemoryAt(value).GetValue();
          return ValueType::DIRECT;
        }
        catch(const std::exception& e)
        {
          throw std::runtime_error(arg + " is not a valid memory address. 0 - 31 is valid. " + ProgramFiles::LineinfoToString(lineinfo));
        }
      }
      else {
        try {
          value = std::stoi(arg);
          return ValueType::PLAIN;
        }
        catch(const std::exception& e)
        {
          std::cout << e.what() << std::endl;
          throw std::runtime_error(arg + " is not a valid number. " + ProgramFiles::LineinfoToString(lineinfo));
        }
      }
    }
  };
}
