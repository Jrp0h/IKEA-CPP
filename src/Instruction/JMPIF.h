#pragma once

#include <map>
#include <string>

#include "Instruction.h"
#include "Lineinfo.h"
#include "ProgramFiles.h"
#include "ProgramState.h"
#include "ValueParser.h"

namespace IKEA::Instruction {
   class JMPIF : public Instruction {
   public:
      JMPIF(std::string tag, bool value) : Instruction(tag), m_Value(value)  {}
      
   protected:
      bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
         if(parts.size() != 3)
            throw std::runtime_error("Invalid argument length at " + ProgramFiles::LineinfoToString(lineinfo));

         int value1;
         int value2;

         ValueType vt1 = ValueParser::Parse(parts[0], value1, lineinfo);
         ValueType vt2 = ValueParser::Parse(parts[1], value2, lineinfo);

         if(vt1 == ValueType::PLAIN && vt1 == ValueType::PLAIN)
         {
            if(value1 == value2)
               throw std::runtime_error("Always true, use JMP insted." + ProgramFiles::LineinfoToString(lineinfo));
            else 
               throw std::runtime_error("Always false, remove." + ProgramFiles::LineinfoToString(lineinfo));
         }

         if((value1 == value2) == m_Value)
            ProgramState::SetNextLine(ProgramState::GetSectionLocation(parts[2], lineinfo) + 1);

         return true;
      }

   private:
      bool m_Value;
   };
}
