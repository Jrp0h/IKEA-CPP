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

class INC : public Instruction {
public:
   INC() : Instruction("INC") { }

protected:
   bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
      if(parts.size() != 1)
         throw std::runtime_error("Invalid argument length at " + ProgramFiles::LineinfoToString(lineinfo));

      int vMemory = 0;

      ValueType vtMemory = ValueParser::Parse(parts[0], vMemory, lineinfo, true);

      if(vtMemory == ValueType::PLAIN)
         throw std::runtime_error("Memory address cant be Plain, requires # before number" + ProgramFiles::LineinfoToString(lineinfo));

      Register::SetMemoryAt(vMemory, Register::GetMemoryAt(vMemory) + 1);

      return true;
   }
};
