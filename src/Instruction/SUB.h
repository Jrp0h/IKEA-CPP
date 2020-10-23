#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Instruction.h"
#include "Lineinfo.h"
#include "ProgramFiles.h"
#include "ProgramState.h"
#include "ValueParser.h"

#include "Callstack.h"

#include "Exception/InvalidArgumentCountException.h"
#include "Exception/InvalidSyntaxException.h"

using namespace IKEA::Exception;

namespace IKEA::Instruction {
class SUB : public Instruction {
public:
   SUB() : Instruction("SUB") { }

protected:
   bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
      if(parts.size() < 2 || parts.size() > 3)
         throw InvalidArgumentCountException("Invalid argument count.", lineinfo);

      int vMemory = 0;
      ValueType vtMemory = ValueParser::Parse(parts[0], vMemory, lineinfo, true);

      if(vtMemory == ValueType::PLAIN)
         throw InvalidSyntaxException("Memory address can't be plain, requires # before number.", lineinfo);

      int vNum1 = 0;
      ValueType vtNum1;

      int num2Part;

      // arg1 -= arg2
      // mem of arg1 = value of arg1 - value of arg2
      if(parts.size() == 2)
      {
         vNum1 = vMemory;

         if(vtMemory == ValueType::VAR)
         {
            vNum1 = Register::GetMemoryAt(vMemory).GetValue();
         }

         num2Part = 1;
      }
      else if(parts.size() == 3)
      {
         vtNum1 = ValueParser::Parse(parts[1], vNum1, lineinfo);
         num2Part = 2;
      }

      int vNum2 = 0;

      ValueType vtNum2 = ValueParser::Parse(parts[num2Part], vNum2, lineinfo);

      Register::SetMemoryAt(vMemory, vNum1 - vNum2);

      return true;
   }
};
}
