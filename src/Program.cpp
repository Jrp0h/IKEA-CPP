#include "Program.h"

#include <iostream>
#include <sstream>
#include <algorithm>

#include "ProgramFiles.h"
#include "ProgramState.h"
#include "Str.h"

#include "Memory/Register.h"

#include "Instruction/Instructions.h"

#include "Exception/InvalidSyntaxException.h"
#include "Exception/UnknownInstructionException.h"


using namespace IKEA::Instruction;
using namespace IKEA::Memory;
using namespace IKEA::Exception;

namespace IKEA {

  void Program::Load(const std::string &path) {
    ProgramFiles::Load(path);
    ProgramState::FindSegments();

    Register::Initialize();

    InitInstructions();
  }

  void Program::Run() {
    while(ReadNextLine());
  }

  bool Program::ReadNextLine() {
    int linenr = ProgramState::StepForward();
    if(ProgramFiles::EndOfProgram(linenr))
      return false;

    std::string line = ProgramFiles::GetRealLine(linenr);

    if(line.find("FUN") == 0)
    {
      if(m_IsInFunction || Callstack::Size() > 0)
          throw InvalidSyntaxException("Tried declaring a function before closing another function. Nested functions are not allowed.", ProgramFiles::LineinfoFromRealline(linenr));

      m_IsInFunction = true;
      return true;
    }

    if(line.find("EFUN") == 0)
    {
      // If no function is called, then check validation
      // else just act like RET
      if(Callstack::Size() <= 0)
      {
        if(!m_IsInFunction)
          throw InvalidSyntaxException("Tried closing a function before opening.", ProgramFiles::LineinfoFromRealline(linenr));

        m_IsInFunction = false;
        return true;
      }
      else {
        line = "RET";
      }
    }

    // Skip empty lines and functionlines
    if(line == "" || m_IsInFunction)
    {
      return true;
    }

    for(auto instruction : m_Instructions)
    {
      if(instruction->Parse(line, ProgramFiles::LineinfoFromRealline(linenr)))
      {
        return true;
      }
    }

    if(line.find("SEC") != 0)
        throw UnknownInstructionException("Unparseable line.", ProgramFiles::LineinfoFromRealline(linenr));

    return true;
  }

  void Program::InitInstructions() {
    // Reset to avoid duplications
    m_Instructions = std::vector<Instruction::Instruction*>();

    m_Instructions.push_back(std::move(new PRNT()));
    m_Instructions.push_back(std::move(new PRNTV()));
    m_Instructions.push_back(std::move(new PRNTM()));

    m_Instructions.push_back(std::move(new CALL()));
    m_Instructions.push_back(std::move(new RET()));

    m_Instructions.push_back(std::move(new JMP()));
    m_Instructions.push_back(std::move(new ConditionJMP("JMPZ", 0)));
    m_Instructions.push_back(std::move(new ConditionJMP("JMPO", 1)));
    m_Instructions.push_back(std::move(new JMPIF("JMPT", true)));
    m_Instructions.push_back(std::move(new JMPIF("JMPF", false)));

    m_Instructions.push_back(std::move(new MOV()));
    m_Instructions.push_back(std::move(new VAR()));

    m_Instructions.push_back(std::move(new ChangeONE("INC", true)));
    m_Instructions.push_back(std::move(new ChangeONE("DEC", false)));

    m_Instructions.push_back(std::move(new DynamicArgs("ADD", OperatorType::ADD)));
    m_Instructions.push_back(std::move(new DynamicArgs("SUB", OperatorType::SUB)));
    m_Instructions.push_back(std::move(new DynamicArgs("AND", OperatorType::AND)));
    m_Instructions.push_back(std::move(new DynamicArgs("OR", OperatorType::OR)));
    m_Instructions.push_back(std::move(new DynamicArgs("XOR", OperatorType::XOR)));

    m_Instructions.push_back(std::move(new Rotate("ROTL", RotationType::ROTATE_LEFT)));
    m_Instructions.push_back(std::move(new Rotate("ROTR", RotationType::ROTATE_RIGHT)));
    m_Instructions.push_back(std::move(new Rotate("SHFL", RotationType::SHIFT_LEFT)));
    m_Instructions.push_back(std::move(new Rotate("SHFR", RotationType::SHIFT_RIGHT)));
  }

  void Program::AddInstruction(Instruction::Instruction& instruction)
  {
    m_Instructions.push_back(&instruction);
  }
}
