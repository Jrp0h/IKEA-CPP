#include <iostream>
#include <sstream>
#include <algorithm>

#include "Program.h"
#include "Str.h"

#include "Instruction/Instruction.h"
#include "Instruction/PRNT.h"

void Program::Load(const std::string &path) {
  File f(path);
  m_Files.push_back(f);

  m_LineInfos = std::vector<Lineinfo>();
  m_RealLines = f.GetLines();

  for (int i = 0; i < f.GetLines().size(); i++) {
    m_LineInfos.push_back(Lineinfo(0, i + 1, i));
  }

  Import();
  Clean();
  InitInstructions();

#if IKEA_DEBUG
  for(auto line : m_RealLines)
  {
    std::cout << line << std::endl;
  }
#endif
}

void Program::Import() {

  for (int i = 0; i < m_RealLines.size(); i++) {
    if (m_RealLines[i].find("IMP") == 0) {
      std::string path = m_RealLines[i].substr(m_RealLines[i].find(" ") + 1);

      if (path == "")
        throw std::runtime_error("Missing arguments in " +
                                 LineinfoToString(LineinfoFromRealline(i)));

      // Remove opening "
      if (path.find("\"") == 0)
        path = path.erase(0, 1);

      // Remove closeing "
      if (path.find("\"") == path.length() - 1)
        path = path.erase(path.length() - 1);

      File f(path);

      InsertLines(i, f.GetLines(), m_Files.size());

      Import();
      break;
    }
  }
}

void Program::Clean() {

  for(int i = 0; i < m_RealLines.size(); i++)
  {
    auto commentPos = m_RealLines[i].find(";");

    if(commentPos != std::string::npos)
      m_RealLines[i] = m_RealLines[i].substr(0, commentPos);

    Str::Trim(m_RealLines[i]);
  }
}

void Program::Run() {
  ReadNextLine();
}

void Program::ReadNextLine() {
  m_CurrentLine = m_NextLine++;

  if(m_CurrentLine == m_RealLines.size())
    return;

  if(m_RealLines[m_CurrentLine].find("FUN") == 0)
  {
    if(m_IsInFunction)
      throw std::runtime_error("Tried declaring a function before closing another function. Nested functions are not allowed" + LineinfoToString(LineinfoFromRealline(m_CurrentLine)));

    m_IsInFunction = true;
    ReadNextLine();
    return;
  }

  if(m_RealLines[m_CurrentLine].find("EFUN") == 0)
  {
    if(!m_IsInFunction)
      throw std::runtime_error("Tried closing a function before opening." + LineinfoToString(LineinfoFromRealline(m_CurrentLine)));

    m_IsInFunction = false;
    ReadNextLine();
    return;
  }

  // Skip empty lines and functionlines
  if(m_RealLines[m_CurrentLine] == "" || m_IsInFunction)
  {
    ReadNextLine();
    return;
  }

  for(auto instruction : m_Instructions)
  {
    if(instruction.Parse(m_RealLines[m_CurrentLine], LineinfoFromRealline(m_CurrentLine)))
    {
      ReadNextLine();
      return;
    }
  }

  if(m_RealLines[m_CurrentLine].find("SEC") != 0)
      throw std::runtime_error("Unparseable line. " + LineinfoToString(LineinfoFromRealline(m_CurrentLine)));
}

void Program::InsertLines(int start, std::vector<std::string> lines,
                          int newFileId) {

  std::vector<std::string> tmpRealLines;
  std::vector<Lineinfo> tmpLineInfos;

  tmpRealLines.resize(m_RealLines.size() + lines.size() - 1);
  tmpLineInfos.resize(m_LineInfos.size() + lines.size() - 1);

  for (int i = 0; i < start; i++) {
    tmpRealLines[i] = m_RealLines[i];
    tmpLineInfos[i] = m_LineInfos[i];
  }

  for (int i = 0; i < lines.size(); i++) {
    tmpRealLines[i + start] = lines[i];
    tmpLineInfos[i + start] = Lineinfo(newFileId, i + 1, i + start);
  }

  for (int i = start + lines.size() - 1; i < tmpLineInfos.size(); i++) {
    tmpLineInfos[i].m_RealLine += start;
  }

  for (int i = start; i < m_RealLines.size() - 1; i++) {
    tmpRealLines[i + lines.size()] = m_RealLines[i + 1];
  }

  m_RealLines = tmpRealLines;
  m_LineInfos = tmpLineInfos;
}

std::string Program::LineinfoToString(Lineinfo lineinfo) {
  std::stringstream ss;
  ss << "File: " << m_Files[lineinfo.m_FileIndex].GetName() << " at line "
     << lineinfo.m_FileLine << std::endl;
  return ss.str();
}

Lineinfo Program::LineinfoFromRealline(int realLine) {

  for (int i = 0; i < m_LineInfos.size(); i++) {
    if (m_LineInfos[i].m_RealLine == realLine)
      return m_LineInfos[i];
  }

  throw std::runtime_error("Failed finding lineinfo from real line: " +
                           std::to_string(realLine));
}

void Program::SetNextLine(int line) {
  m_NextLine = line;
}

int Program::GetNextLine() {
  return m_NextLine;
}

void Program::InitInstructions() {
  m_Instructions.push_back(PRNT());
}
