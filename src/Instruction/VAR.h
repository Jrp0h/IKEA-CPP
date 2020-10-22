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

class VAR : public Instruction {
public:
   VAR() : Instruction("VAR") { }

protected:
   bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
      if(parts.size() != 2)
         throw std::runtime_error("Invalid argument length at " + ProgramFiles::LineinfoToString(lineinfo));

      int vValue = 0;

      ValueType vtValue = ValueParser::Parse(parts[1], vValue, lineinfo);

      // std::cout << "p1 " << parts[0] << " p2 " << parts[1] << std::endl;
      // std::cout << "Setting " << parts[0] << " to " << vValue << std::endl << std::endl;

      Register::SetVar(parts[0], vValue);
      // Register::PrintVars();

      return true;
   }
};
