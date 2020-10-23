#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Instruction/Instruction.h"
#include "Lineinfo.h"
#include "ProgramFiles.h"
#include "ProgramState.h"

#include "Callstack.h"

namespace IKEA::Instruction {

class RET : public Instruction {
public:
   RET() : Instruction("RET") { }

protected:
   bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {

      ProgramState::SetNextLine(Callstack::Pop());
      return true;

   }
};
}
