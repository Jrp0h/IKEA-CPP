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

class VAR : public Instruction {
public:
   VAR() : Instruction("VAR") { }

protected:
   bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
      if(parts.size() != 2)
         throw InvalidArgumentCountException("Invalid argument count.", lineinfo);

      int vValue = 0;

      ValueType vtValue = ValueParser::Parse(parts[1], vValue, lineinfo, true);

      Register::SetVar(parts[0], vValue);

      return true;
   }
};
}
