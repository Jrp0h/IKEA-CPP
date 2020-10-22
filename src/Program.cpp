#include "Program.h"

#include <iostream>
#include <sstream>
#include <algorithm>

#include "ProgramFiles.h"
#include "ProgramState.h"
#include "Str.h"

#include "Memory/Register.h"

#include "Instruction/Instructions.h"


void Program::Load(const std::string &path) {
  ProgramFiles::Load(path);
  ProgramState::FindSegments();

  Register::Initialize();

  InitInstructions();
}

void Program::Run() {
  ReadNextLine();
  while(ReadNextLine());
}

bool Program::ReadNextLine() {
  int linenr = ProgramState::StepForward();
  if(ProgramFiles::EndOfProgram(linenr))
    return false;

  std::string line = ProgramFiles::GetRealLine(linenr);

  if(line.find("FUN") == 0)
  {
    if(m_IsInFunction)
        throw std::runtime_error("Tried declaring a function before closing another function. Nested functions are not allowed. " + ProgramFiles::LineinfoToString(linenr));

    m_IsInFunction = true;
    // ReadNextLine();
    return true;
  }

  if(line.find("EFUN") == 0)
  {
    if(!m_IsInFunction)
      throw std::runtime_error("Tried closing a function before opening. " + ProgramFiles::LineinfoToString(linenr));

    m_IsInFunction = false;
    // ReadNextLine();
    return true;
  }

  // Skip empty lines and functionlines
  if(line == "" || m_IsInFunction)
  {
    ReadNextLine();
    return true;
  }

  for(auto instruction : m_Instructions)
  {
    if(instruction->Parse(line, ProgramFiles::LineinfoFromRealline(linenr)))
    {
      ReadNextLine();
      return true;
    }
  }

  if(line.find("SEC") != 0)
      throw std::runtime_error("Unparseable line. " + ProgramFiles::LineinfoToString(linenr));

  return true;
}

void Program::InitInstructions() {
  m_Instructions.push_back(std::move(new PRNT()));
  m_Instructions.push_back(std::move(new PRNTV()));
  m_Instructions.push_back(std::move(new CALL()));
  m_Instructions.push_back(std::move(new RET()));
  m_Instructions.push_back(std::move(new ConditionJMP("JMPZ", 0)));
  m_Instructions.push_back(std::move(new ConditionJMP("JMPO", 1)));
  m_Instructions.push_back(std::move(new JMP()));
  m_Instructions.push_back(std::move(new JMPIF("JMPT", true)));
  m_Instructions.push_back(std::move(new JMPIF("JMPF", false)));
  m_Instructions.push_back(std::move(new MOV()));
  m_Instructions.push_back(std::move(new VAR()));
}

void Program::AddInstruction(Instruction& instruction)
{
  m_Instructions.push_back(&instruction);
}
