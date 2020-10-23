#pragma once

#include <map>
#include <string>

#include "Instruction.h"
#include "Lineinfo.h"
#include "ProgramFiles.h"

#include "Exception/InvalidSyntaxException.h"
#include "Exception/UndefinedLocationException.h"

using namespace IKEA::Exception;

namespace IKEA::Instruction {
class Segment : public Instruction {
public:
   Segment(std::string tag, std::string type) : Instruction(tag), m_Type(type)  {}
   
   void Print()
   {
      for(auto location : m_Locations)
      {
         std::cout << location.first << ":" << location.second << std::endl;
      }
   }

   int GetLocation(std::string name, Lineinfo lineinfo)
   {
      if(m_Locations.find(name) == m_Locations.end())
         throw UndefinedLocationException("No " + m_Type + " named " + name + " found.", lineinfo);

      return m_Locations[name];
   }
protected:
   bool ParseLine(std::vector<std::string> parts, Lineinfo lineinfo) override {
      if(parts.size() != 1)
         throw InvalidArgumentCountException("Invalid argument count.", lineinfo);

      // Remove : if it exists
      if (parts[0].find(":") == parts[0].length() - 1)
        parts[0] = parts[0].erase(parts[0].length() - 1);

      if(parts[0] == "")
         throw InvalidSyntaxException(m_Type + " must have an identifier.", lineinfo);

      if(m_Locations.find(parts[0]) == m_Locations.end())
         m_Locations.insert(std::make_pair(parts[0], lineinfo.m_RealLine));
      else
         throw InvalidSyntaxException(m_Type + " with identifier " + parts[0] + " is already declared.", lineinfo);

      return true;
   }

private:
   std::string m_Type;
   std::map<std::string, int> m_Locations;
};
}
