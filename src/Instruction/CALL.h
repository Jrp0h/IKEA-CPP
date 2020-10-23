#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Instruction.h"
#include "Lineinfo.h"
#include "ProgramFiles.h"
#include "ProgramState.h"

#include "Callstack.h"
#include "Exception/InvalidArgumentCountException.h"
#include "Exception/InvalidSyntaxException.h"

using namespace IKEA::Exception;

namespace IKEA::Instruction {
   class CALL : public Instruction {
   public:
      CALL() : Instruction("CALL") { }

   protected:
      bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
         if(parts.size() != 1)
            throw InvalidArgumentCountException("Invalid argument count.", lineinfo);

         ProgramState::SetNextLine(ProgramState::GetFunctionLocation(parts[0], lineinfo) + 1);
         Callstack::Push(lineinfo.m_RealLine + 1);

         return true;
      }
   };
}
