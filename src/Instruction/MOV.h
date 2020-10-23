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
   class MOV : public Instruction {
   public:
      MOV() : Instruction("MOV") { }

   protected:
      bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
         if(parts.size() != 2)
            throw InvalidArgumentCountException("Invalid argument count.", lineinfo);

         int vMemory = 0;
         int vValue = 0;

         ValueType vtMemory = ValueParser::Parse(parts[0], vMemory, lineinfo, true);
         ValueType vtValue = ValueParser::Parse(parts[1], vValue, lineinfo);

         if(vtMemory == ValueType::PLAIN)
            throw InvalidSyntaxException("Memory address can't be plain, requires # before number.", lineinfo);

         Register::SetMemoryAt(vMemory, vValue);

         return true;
      }
   };
}
