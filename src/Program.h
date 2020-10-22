#pragma once

#include <string>
#include <vector>

#include "File.h"
#include "Lineinfo.h"
#include "Instruction/Instruction.h"

class Program {
public:
   static void Load(const std::string &file);
   static void Run();

   
   static void AddInstruction(Instruction& instruction);

private:
   static void FindSegments();
   static void InitInstructions();

   static bool ReadNextLine();
private:
   inline static std::vector<Instruction*> m_Instructions;
  inline static bool m_IsInFunction = false;
};
