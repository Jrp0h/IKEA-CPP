#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Instruction/Instruction.h"
#include "Lineinfo.h"
#include "Memory/Register.h"

class PRNTV : public Instruction {
public:
   PRNTV() : Instruction("PRNTV") { }

protected:
   bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
      Register::PrintVars();
      return true;
   }
};
