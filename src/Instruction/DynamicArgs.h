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

   enum class OperatorType { ADD, SUB, AND, OR, XOR, };

   class DynamicArgs : public Instruction {
      public:
         DynamicArgs(std::string tag, OperatorType type) : Instruction(tag), m_Type(type) { }

      protected:
         bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {

            if(parts.size() < 2 || parts.size() > 3)
               throw InvalidArgumentCountException("Invalid argument count.", lineinfo);

            Memory::Memory vMemory = 0;
            ValueType vtMemory = ValueParser::Parse(parts[0], vMemory, lineinfo, true);

            if(vtMemory == ValueType::PLAIN)
               throw InvalidSyntaxException("Memory address can't be plain, requires # before number.", lineinfo);

            Memory::Memory vNum1 = 0;

            int num2Part;

            // arg1 = arg1 (operator) arg2
            // mem of arg1 = value of arg1 (operator) value of arg2
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
               ValueParser::Parse(parts[1], vNum1, lineinfo);
               num2Part = 2;
            }

            Memory::Memory vNum2 = 0;

            ValueType vtNum2 = ValueParser::Parse(parts[num2Part], vNum2, lineinfo);

            switch(m_Type)
            {
               case OperatorType::ADD:
                  Register::SetMemoryAt(vMemory.GetValue(), vNum1 + vNum2);
                  break;
               case OperatorType::SUB:
                  Register::SetMemoryAt(vMemory.GetValue(), vNum1 - vNum2);
                  break;
               case OperatorType::AND:
                  Register::SetMemoryAt(vMemory.GetValue(), vNum1 & vNum2);
                  break;
               case OperatorType::OR:
                  Register::SetMemoryAt(vMemory.GetValue(), vNum1 | vNum2);
                  break;
               case OperatorType::XOR:
                  Register::SetMemoryAt(vMemory.GetValue(), vNum1 ^ vNum2);
                  break;
            }

            return true;
         }
      private:
         OperatorType m_Type;
   };


}
