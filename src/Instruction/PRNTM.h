#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Instruction/Instruction.h"
#include "Lineinfo.h"
#include "Memory/Register.h"

using namespace IKEA::Memory;

namespace IKEA::Instruction {
   class PRNTM : public Instruction {
      public:
         PRNTM() : Instruction("PRNTM") { }

      protected:
         bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
            Register::PrintMemory();
            return true;
         }
   };
}
