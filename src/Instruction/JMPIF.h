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
   
   enum class ComparisonType { 
      EQUAL = 1, 
      NOT_EQUAL, 
      LESS, 
      GREATER,
      LESS_OR_EQUAL,
      GREATER_OR_EQUAL
   };

   class JMPIF : public Instruction {
   public:
      JMPIF(std::string tag, ComparisonType type) : Instruction(tag), m_Type(type)  {}
      
   protected:
      bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
         if(parts.size() != 3)
            throw InvalidArgumentCountException("Invalid argument count.", lineinfo);

         Memory::Memory value1;
         Memory::Memory value2;

         ValueType vt1 = ValueParser::Parse(parts[0], value1, lineinfo);
         ValueType vt2 = ValueParser::Parse(parts[1], value2, lineinfo);

         if(vt1 == ValueType::PLAIN && vt2 == ValueType::PLAIN)
         {
            if(value1 == value2)
               throw UnnecessaryComparisonException("Always true, use JMP insted.", lineinfo);
            else 
               throw UnnecessaryComparisonException("Always false, remove.", lineinfo);
         }

         switch(m_Type)
         {
            case ComparisonType::EQUAL:
               if(value1 == value2)
                  ProgramState::SetNextLine(ProgramState::GetSectionLocation(parts[2], lineinfo) + 1);
               break;
            case ComparisonType::NOT_EQUAL:
               if(value1 != value2)
                  ProgramState::SetNextLine(ProgramState::GetSectionLocation(parts[2], lineinfo) + 1);
               break;
            case ComparisonType::LESS:
               if(value1 < value2)
                  ProgramState::SetNextLine(ProgramState::GetSectionLocation(parts[2], lineinfo) + 1);
               break;
            case ComparisonType::GREATER:
               if(value1 > value2)
                  ProgramState::SetNextLine(ProgramState::GetSectionLocation(parts[2], lineinfo) + 1);
               break;
            case ComparisonType::LESS_OR_EQUAL:
               if(value1 <= value2)
                  ProgramState::SetNextLine(ProgramState::GetSectionLocation(parts[2], lineinfo) + 1);
               break;
            case ComparisonType::GREATER_OR_EQUAL:
               if(value1 >= value2)
                  ProgramState::SetNextLine(ProgramState::GetSectionLocation(parts[2], lineinfo) + 1);
               break;
         }

         return true;
      }

   private:
      ComparisonType m_Type;
   };
}
