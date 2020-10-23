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
#include "Exception/UnnecesseryComparisonException.h"

using namespace IKEA::Exception;

namespace IKEA::Instruction {
   class JMPIF : public Instruction {
   public:
      JMPIF(std::string tag, bool value) : Instruction(tag), m_Value(value)  {}
      
   protected:
      bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
         if(parts.size() != 3)
            throw InvalidArgumentCountException("Invalid argument count.", lineinfo);

         int value1;
         int value2;

         ValueType vt1 = ValueParser::Parse(parts[0], value1, lineinfo);
         ValueType vt2 = ValueParser::Parse(parts[1], value2, lineinfo);

         if(vt1 == ValueType::PLAIN && vt1 == ValueType::PLAIN)
         {
            if(value1 == value2)
               throw UnnecessaryComparisonException("Always true, use JMP insted.", lineinfo);
            else 
               throw UnnecessaryComparisonException("Always false, remove.", lineinfo);
         }

         if((value1 == value2) == m_Value)
            ProgramState::SetNextLine(ProgramState::GetSectionLocation(parts[2], lineinfo) + 1);

         return true;
      }

   private:
      bool m_Value;
   };
}
