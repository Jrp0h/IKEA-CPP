#include "Register.h"

#include <exception>

#include "ProgramFiles.h"
#include "ProgramState.h"

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
      throw std::runtime_error("Cannot access memory " + std::to_string(slot) + ". Max is 32");

    m_Memory[slot].SetValue(value);
  }

  void Register::SetMemoryAt(int slot, bool value[16]) {
    if(slot >= m_Memory.size())
      throw std::runtime_error("Cannot access memory " + std::to_string(slot) + ". Max is 32");

    m_Memory[slot].SetValue(value);
  }

  void Register::SetMemoryAt(int slot, Memory value) {
    if(slot >= m_Memory.size())
      throw std::runtime_error("Cannot access memory " + std::to_string(slot) + ". Max is 32");

    m_Memory[slot] = value;
  }

  Memory& Register::GetMemoryAt(int slot) {
    if(slot >= m_Memory.size())
      throw std::runtime_error("Cannot access memory " + std::to_string(slot) + ". Max is 32");

    return m_Memory[slot];
  }

  Memory& Register::GetVar(std::string name){
    if(m_Vars.find(name) == m_Vars.end())
      throw std::runtime_error("Undeclared var " + name + " at " + ProgramFiles::LineinfoToString(ProgramState::GetCurrentLine()));

    return m_Vars[name];
  }

  void Register::SetVar(std::string name, int value) {
    if(m_Vars.find(name) == m_Vars.end())
      m_Vars.insert(std::make_pair(name, value));
    else
      m_Vars[name] = Memory(value);
  }

  void Register::PrintVars(){
    std::cout << std::endl << std::endl << "Variables" << std::endl;
    for(auto var : m_Vars)
    {
      std::cout << var.first << " &" << var.second.GetValue() << " ";
      if(var.second.GetValue() >= 32)
        std::cout << "Invalid Memory Address" << std::endl;
      else
        std::cout << "$" << m_Memory[var.second.GetValue()].GetValue() << std::endl;
    }

    if(m_Vars.size() <= 0)
      std::cout << "NO VARIABLES SET" << std::endl;

  }

  void Register::PrintMemory(){
    std::cout << std::endl << std::endl << "Variables" << std::endl;
    for(int i = 0; i < 32; i++)
    {
      std::cout << "#" << i << " : " << m_Memory[i].ToBinaryString() << "(" << m_Memory[i].GetValue() << ")" << std::endl; 
    }
  }
}
