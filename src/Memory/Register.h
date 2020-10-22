#pragma once

#include <array>
#include <map>
#include <string>

#include "Memory.h"

class Register {
public:
  static void Initialize();

  static void SetMemoryAt(int slot, int value);
  static void SetMemoryAt(int slot, std::array<bool, 16> value);

  static Memory& GetMemoryAt(int slot);

  static Memory& GetVar(std::string name);
  static void SetVar(std::string name, int value);

  static void PrintVars();
private:
  inline static std::array<Memory, 32> m_Memory;
  inline static std::map<std::string, Memory> m_Vars;
};
