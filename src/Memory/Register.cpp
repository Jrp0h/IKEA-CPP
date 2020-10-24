#include "Register.h"

#include <exception>

#include "ProgramFiles.h"
#include "ProgramState.h"

#include "Exception/MemoryOutOfRangeException.h"
#include "Exception/UndeclaredVariableException.h"

using namespace IKEA::Exception;

namespace IKEA::Memory {
  void Register::Initialize()
  {
    m_Memory = std::array<Memory, 32>();
    m_Vars = std::map<std::string, Memory>();

    for(auto& mem : m_Memory)
    {
      mem.SetValue(0);
    }
  }

  void Register::SetMemoryAt(int slot, int value) {
    if(slot >= m_Memory.size())
      throw MemoryOutOfRangeException("Can't access memory " + std::to_string(slot) + ". 0-31 is valid.", ProgramFiles::LineinfoFromRealline(ProgramState::GetCurrentLine()));

    m_Memory[slot].SetValue(value);
  }

  void Register::SetMemoryAt(int slot, bool value[16]) {
    if(slot >= m_Memory.size())
      throw MemoryOutOfRangeException("Can't access memory " + std::to_string(slot) + ". 0-31 is valid.", ProgramFiles::LineinfoFromRealline(ProgramState::GetCurrentLine()));

    m_Memory[slot].SetValue(value);
  }

  void Register::SetMemoryAt(int slot, Memory value) {
    if(slot >= m_Memory.size())
      throw MemoryOutOfRangeException("Can't access memory " + std::to_string(slot) + ". 0-31 is valid.", ProgramFiles::LineinfoFromRealline(ProgramState::GetCurrentLine()));

    m_Memory[slot] = value;
  }

  Memory& Register::GetMemoryAt(Memory slot) {
    if(slot.GetValue() >= m_Memory.size())
      throw MemoryOutOfRangeException("Can't access memory " + std::to_string(slot.GetValue()) + ". 0-31 is valid.", ProgramFiles::LineinfoFromRealline(ProgramState::GetCurrentLine()));

    return m_Memory[slot.GetValue()];
  }

  Memory& Register::GetVar(std::string name){
    if(m_Vars.find(name) == m_Vars.end())
      throw UndeclaredVariableException("Undeclared var " + name + ".", ProgramFiles::LineinfoFromRealline(ProgramState::GetCurrentLine()));

    return m_Vars[name];
  }

  void Register::SetVar(std::string name, int value) {
    if(m_Vars.find(name) == m_Vars.end())
      m_Vars.insert(std::make_pair(name, value));
    else
      m_Vars[name] = Memory(value);
  }

  void Register::SetVar(std::string name, Memory value) {
    if(m_Vars.find(name) == m_Vars.end())
      m_Vars.insert(std::make_pair(name, value));
    else
      m_Vars[name] = value;
  }

  void Register::PrintVars(){
    std::cout << std::endl << std::endl << "Variables" << std::endl;
    if(m_Vars.size() <= 0)
    {
      std::cout << "NO VARIABLES SET" << std::endl;
      return;
    }

    std::cout << "Name:\t\tAddress:\tValue:" << std::endl; 
    for(auto var : m_Vars)
    {
      std::cout << var.first << "\t\t&" << var.second.GetValue() << " ";
      if(var.second.GetValue() >= 32)
        std::cout << "\t\tInvalid Memory Address" << std::endl;
      else
        std::cout << "\t\t$" << m_Memory[var.second.GetValue()].GetValue() << std::endl;
    }


  }

  void Register::PrintMemory(){

    std::cout << std::endl << std::endl << "Memory:" << std::endl;

    std::cout << "Index:\tBinary:\t\t\tHex:\tDecimal:" << std::endl; 
    for(int i = 0; i < 32; i++)
    {
      std::cout << "#" << i << "\t" << m_Memory[i].ToBinaryString() << "\t" << m_Memory[i].ToHexString() << "\t" << m_Memory[i].GetValue() << std::endl; 
    }

  }
}
