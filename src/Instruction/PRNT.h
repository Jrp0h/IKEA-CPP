#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Instruction/Instruction.h"
#include "Lineinfo.h"
#include "ProgramFiles.h"
#include "ValueParser.h"

namespace IKEA::Instruction {
   class PRNT : public Instruction {
   public:
      PRNT() : Instruction("PRNT") { }

   protected:
      bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
         if(parts.size() != 1)
            throw std::runtime_error("Invalid argument length at " + ProgramFiles::LineinfoToString(lineinfo));
           
         int value;
         ValueType vtValue = ValueParser::Parse(parts[0], value, lineinfo, false, true);
         
         if(vtValue == ValueType::PLAIN)
            std::cout << parts[0] << std::endl;
         else
            std::cout << value << std::endl;

         return true;
      }
   };
}
