#pragma once

#include <string>
#include <sstream>
#include <vector>

#include "Lineinfo.h"
#include "Str.h"

class Instruction {
public:
  Instruction(std::string instruction) : m_Instruction(instruction) {}
  virtual ~Instruction() = default; 

  std::string GetInstruction() { return m_Instruction; }

  bool Parse(std::string line, Lineinfo lineinfo) {
    auto pos = line.find(" ");
    std::string instruction = line.substr(0, pos);
    std::string argLine = line.substr(pos + 1);

    if(instruction != m_Instruction)
      return false;

    std::vector<std::string> args;

    std::istringstream s(argLine);
    std::string a;

    while(std::getline(s, a, ','))
    {
      args.push_back(Str::Trim(a));
    }

    return ParseLine(args, lineinfo);
  }

protected:
  virtual bool ParseLine(std::vector<std::string> args, Lineinfo lineinfo);

protected:
  std::string m_Instruction;

};
