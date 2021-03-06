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

   class NOT : public Instruction {
      public:
         NOT() : Instruction("NOT") {}

      protected:
         bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {

            if(parts.size() != 1 && parts.size() != 2)
               throw InvalidArgumentCountException("Invalid argument count.", lineinfo);

            Memory::Memory vMemory = 0;
            ValueType vtMemory = ValueParser::Parse(parts[0], vMemory, lineinfo, true);

            if(vtMemory == ValueType::PLAIN)
               throw InvalidSyntaxException("Memory address can't be plain, requires # before number.", lineinfo);

            Memory::Memory vNum1 = 0;

            int num2Part;

            // arg1 = !arg1
            // mem of arg1 = !(value of arg1)
            if(parts.size() == 1)
            {
               vNum1 = vMemory;

               if(vtMemory == ValueType::VAR)
               {
                  vNum1 = Register::GetMemoryAt(vMemory).GetValue();
               }
            }
            else if(parts.size() == 2)
            {
               ValueParser::Parse(parts[1], vNum1, lineinfo);
            }

            Register::SetMemoryAt(vMemory.GetValue(), vNum1.NOT());

            return true;
         }
   };
}
