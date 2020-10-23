#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Instruction/Instruction.h"
#include "Lineinfo.h"

namespace IKEA::Instruction {
class PRNT : public Instruction {
public:
   PRNT() : Instruction("PRNT") { }

protected:
   bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
      if(parts.size() == 1)
         std::cout << parts[0] << std::endl;

      return true;
   }
};
}
