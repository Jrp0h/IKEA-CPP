#pragma once

#include "Instruction/Segment.h"
#include "Lineinfo.h"

class ProgramState {
public:
  static void SetNextLine(int line);
  static int GetNextLine();

  static int GetCurrentLine();

  static int StepForward();

  static void FindSegments();

  static int GetSectionLocation(std::string name, Lineinfo lineinfo);
  static int GetFunctionLocation(std::string name, Lineinfo lineinfo);
  
private:
  inline static int m_NextLine = 0;
  inline static int m_CurrentLine = 0;

  inline static Segment m_Sections = Segment("SEC", "Section");
  inline static Segment m_Functions = Segment("FUN", "Function");
};
