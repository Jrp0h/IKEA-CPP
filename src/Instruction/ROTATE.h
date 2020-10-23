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

enum class RotationType { ROTATE_LEFT, ROTATE_RIGHT, SHIFT_LEFT, SHIFT_RIGHT };

class Rotate : public Instruction {
public:
   Rotate(std::string tag, RotationType rt) 
      : Instruction(tag), m_RotationType(rt) { }

protected:
   bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
      if(parts.size() != 2)
         throw InvalidArgumentCountException("Invalid argument count.", lineinfo);

      int vMemory = 0;
      int vValue = 0;

      ValueType vtMemory = ValueParser::Parse(parts[0], vMemory, lineinfo, true);
      ValueType vtValue = ValueParser::Parse(parts[1], vValue, lineinfo);

      if(vtMemory == ValueType::PLAIN)
            throw InvalidSyntaxException("Memory address can't be plain, requires # before number.", lineinfo);

      switch(m_RotationType)
      {
         case RotationType::ROTATE_LEFT:
            Register::GetMemoryAt(vMemory).RotateLeft(vValue);
            break;
         case RotationType::ROTATE_RIGHT:
            Register::GetMemoryAt(vMemory).RotateRight(vValue);
            break;
         case RotationType::SHIFT_LEFT:
            Register::GetMemoryAt(vMemory).ShiftLeft(vValue);
            break;
         case RotationType::SHIFT_RIGHT:
            Register::GetMemoryAt(vMemory).ShiftRight(vValue);
            break;
      }

      return true;
   }

private:
   RotationType m_RotationType;
};
}
