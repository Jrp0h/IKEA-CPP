#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Instruction/Instruction.h"
#include "Lineinfo.h"
#include "ProgramFiles.h"
#include "ValueParser.h"

#include "Exception/InvalidArgumentCountException.h"
#include "Exception/InvalidSyntaxException.h"

using namespace IKEA::Exception;

namespace IKEA::Instruction {
   class PRNT : public Instruction {
   public:
      PRNT() : Instruction("PRNT") { }

   protected:
      bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
         if(parts.size() == 0) {
            std::cout << std::endl;
            return true;
         }

         if(parts.size() != 1 && parts.size() != 2)
            throw InvalidArgumentCountException("Invalid argument count.", lineinfo);

           
         Memory::Memory value;
         ValueType vtValue = ValueParser::Parse(parts[0], value, lineinfo, false, true);
         
         if(vtValue == ValueType::PLAIN)
            std::cout << parts[0] << std::endl;
         else
         {
            // print out value
            if(parts.size() == 1)
               std::cout << value.GetValue() << std::endl;
            // Print out value in the specified format
            else if(parts.size() == 2)
            {
               Str::ToLower(parts[1]);

               if(parts[1] == "hex")
                  std::cout << value.ToHexString() << std::endl;
               else if(parts[1] == "bin")
                  std::cout << value.ToBinaryString() << std::endl;
               else if(parts[1] == "dec")
                  std::cout << value.GetValue() << std::endl;
            }
         }

         return true;
      }
   };
}
