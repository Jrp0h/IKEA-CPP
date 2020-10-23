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
   class ConditionJMP : public Instruction {
      public:
         ConditionJMP(std::string tag, int value) : Instruction(tag), m_Value(value)  {}
         
      protected:
         bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
            if(parts.size() != 2)
               throw InvalidArgumentCountException("Invalid argument count.", lineinfo);

            int value;

            ValueType vt = ValueParser::Parse(parts[0], value, lineinfo);

            if(vt == ValueType::PLAIN)
               throw UnnecessaryComparisonException("Unnecessary comparison, use JMP insted.", lineinfo);

            if(value == m_Value)
               ProgramState::SetNextLine(ProgramState::GetSectionLocation(parts[1], lineinfo) + 1);

            return true;
         }

      private:
         int m_Value;
   };
}
