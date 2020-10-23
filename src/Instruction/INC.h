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
   class INC : public Instruction {
   public:
      INC() : Instruction("INC") { }

   protected:
      bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
         if(parts.size() != 1)
            throw InvalidArgumentCountException("Invalid argument count.", lineinfo);

         int vMemory = 0;

         ValueType vtMemory = ValueParser::Parse(parts[0], vMemory, lineinfo, true);

         if(vtMemory == ValueType::PLAIN)
            throw InvalidSyntaxException("Memory address can't be plain, requires # before number.", lineinfo);

         // Switch VAR and VAR_VALUE
         // Because VAR should change the address the var
         // is pointing to and VAR_VALUE should change the
         // memory at the address the VAR is pointing to
         //
         // Aka i = 5, mem5 = 10
         // &i - 1: i = 4, mem5 = 10
         // $i -1: i = 5, mem5 = 9
         if(vtMemory == ValueType::VAR_VALUE)
         {
            vMemory = ValueParser::GetMemoryLocationFromVar(parts[0]);
         }
         else if(vtMemory == ValueType::VAR)
         {
            auto varName = parts[0].erase(0, 1);
            Register::SetVar(varName, Register::GetVar(varName) + 1);
            return true;
         }
         
         Register::SetMemoryAt(vMemory, Register::GetMemoryAt(vMemory) + 1);

         return true;
      }
   };
}
