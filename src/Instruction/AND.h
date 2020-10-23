#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Instruction.h"
#include "Lineinfo.h"
#include "ProgramFiles.h"
#include "ProgramState.h"
#include "ValueParser.h"
#include "Memory/Memory.h"

#include "Callstack.h"
#include "Exception/InvalidArgumentCountException.h"
#include "Exception/InvalidSyntaxException.h"

using namespace IKEA::Exception;

using namespace IKEA::Memory;

namespace IKEA::Instruction {
   class AND : public Instruction {
      public:
         AND() : Instruction("AND") { }

      protected:
         bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
            if(parts.size() < 2 || parts.size() > 3)
               throw InvalidArgumentCountException("Invalid argument count.", lineinfo);

            int vMemory = 0;
            ValueType vtMemory = ValueParser::Parse(parts[0], vMemory, lineinfo, true);

            if(vtMemory == ValueType::PLAIN)
               throw InvalidSyntaxException("Memory address can't be plain, requires # before number.", lineinfo);

            int vNum1 = 0;
            ValueType vtNum1;

            int num2Part;

            // arg1 &= arg2
            // mem of arg1 = value of arg1 & value of arg2
            if(parts.size() == 2)
            {
               vNum1 = vMemory;

               if(vtMemory == ValueType::VAR)
               {
                  vNum1 = Register::GetMemoryAt(vMemory).GetValue();
               }

               num2Part = 1;
            }
            else if(parts.size() == 3)
            {
               vtNum1 = ValueParser::Parse(parts[1], vNum1, lineinfo);
               num2Part = 2;
            }

            int vNum2 = 0;
            ValueType vtNum2 = ValueParser::Parse(parts[num2Part], vNum2, lineinfo);

            Memory::Memory mem1(vNum1);
            Memory::Memory mem2(vNum2);

            Register::SetMemoryAt(vMemory, mem1 & mem2);

            return true;
         }
   };
}
