#pragma once

#include <map>
#include <string>

#include "Instruction.h"
#include "Lineinfo.h"
#include "ProgramFiles.h"
#include "ProgramState.h"
#include "ValueParser.h"

#include "Exception/InvalidArgumentCountException.h"
#include "Exception/InvalidSyntaxException.h"

using namespace IKEA::Exception;

namespace IKEA::Instruction {
   class JMP : public Instruction {
   public:
      JMP() : Instruction("JMP"){}
      
   protected:
      bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
         if(parts.size() != 1)
            throw InvalidArgumentCountException("Invalid argument count.", lineinfo);
         
         ProgramState::SetNextLine(ProgramState::GetSectionLocation(parts[0], lineinfo) + 1);

         return true;
      }
   };
}
