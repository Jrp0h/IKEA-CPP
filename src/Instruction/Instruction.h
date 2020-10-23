#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include "Lineinfo.h"
#include "ProgramFiles.h"
#include "Str.h"

namespace IKEA::Instruction {
  class Instruction {
  public:
    Instruction(std::string tag) : m_Tag(tag) {}
    virtual ~Instruction() = default; 

    std::string GetTag() { return m_Tag; }

    virtual bool Parse(std::string line, Lineinfo lineinfo) {
      auto pos = line.find(" ");
      std::string instruction = line.substr(0, pos);
      std::string argLine = line.substr(pos + 1);

      if(instruction != m_Tag)
      {
        if(instruction == m_Tag + ":")
          throw std::runtime_error("Invalid syntax. " + ProgramFiles::LineinfoToString(lineinfo));
        return false;
      }

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
    virtual bool ParseLine(std::vector<std::string> args, Lineinfo lineinfo) = 0;

  protected:
    std::string m_Tag;
  };
}
