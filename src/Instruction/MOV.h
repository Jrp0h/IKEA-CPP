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

namespace IKEA::Instruction {
   class MOV : public Instruction {
   public:
      MOV() : Instruction("MOV") { }

   protected:
      bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
         if(parts.size() != 2)
            throw std::runtime_error("Invalid argument length at " + ProgramFiles::LineinfoToString(lineinfo));

         int vMemory = 0;
         int vValue = 0;

         ValueType vtMemory = ValueParser::Parse(parts[0], vMemory, lineinfo, true);
         ValueType vtValue = ValueParser::Parse(parts[1], vValue, lineinfo);

         if(vtMemory == ValueType::PLAIN)
            throw std::runtime_error("Memory address cant be Plain, requires # before number" + ProgramFiles::LineinfoToString(lineinfo));

         Register::SetMemoryAt(vMemory, vValue);

         return true;
      }
   };
}
