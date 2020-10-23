#include "ProgramState.h"

namespace IKEA {
  void ProgramState::SetNextLine(int line) {
    m_NextLine = line;
  }

  int ProgramState::GetNextLine() {
    return m_NextLine;
  }

  int ProgramState::GetCurrentLine() {
    return m_CurrentLine;
  }

  int ProgramState::StepForward() {
    m_CurrentLine = m_NextLine++;
    return m_CurrentLine;
  }

  void ProgramState::FindSegments(){

    std::vector<std::string> lines = ProgramFiles::GetAllLines();

    for(int i = 0; i < lines.size(); i++)
    {
      if(lines[i] == "")
        continue;

      // Check if line is a section, if not, then check if it's a function
      if(!m_Sections.Parse(lines[i], ProgramFiles::LineinfoFromRealline(i)))
        m_Functions.Parse(lines[i], ProgramFiles::LineinfoFromRealline(i));
    }

  }

  int ProgramState::GetSectionLocation(std::string name, Lineinfo lineinfo)
  {
    return m_Sections.GetLocation(name, lineinfo);
  }

  int ProgramState::GetFunctionLocation(std::string name, Lineinfo lineinfo)
  {
    return m_Functions.GetLocation(name, lineinfo);
  }
}
