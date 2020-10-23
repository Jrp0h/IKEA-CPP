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

namespace IKEA::Instruction {

   class ADD : public Instruction {
      public:
         ADD() : Instruction("ADD") { }

      protected:
         bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
            if(parts.size() < 2)
               throw std::runtime_error("Invalid argument length at " + ProgramFiles::LineinfoToString(lineinfo));

            int vMemory = 0;
            ValueType vtMemory = ValueParser::Parse(parts[0], vMemory, lineinfo, true);

            if(vtMemory == ValueType::PLAIN)
               throw std::runtime_error("Memory address cant be Plain, requires # before number" + ProgramFiles::LineinfoToString(lineinfo));

            int vNum1 = 0;
            ValueType vtNum1;

            int num2Part;

            if(parts.size() == 2)
            {
               vNum1 = vMemory;
               vtNum1 = vtMemory;
               num2Part = 1;
            }
            else if(parts.size() == 3)
            {
               vtNum1 = ValueParser::Parse(parts[1], vNum1, lineinfo);
               num2Part = 2;
            }

            int vNum2 = 0;

            ValueType vtNum2 = ValueParser::Parse(parts[num2Part], vNum2, lineinfo);

            Register::SetMemoryAt(vMemory, vNum1 + vNum2);

            return true;
         }
   };
}
