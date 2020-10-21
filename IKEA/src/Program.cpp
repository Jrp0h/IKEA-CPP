#include <iostream>
#include <sstream>

#include "Program.h"

void Program::Load(const std::string &path) {
  File f(path);
  m_Files.push_back(f);

  m_LineInfos = std::vector<Lineinfo>();
  m_RealLines = f.GetLines();

  for (int i = 0; i < f.GetLines().size(); i++) {
    m_LineInfos.push_back(Lineinfo(0, i + 1, i));
  }

  Import();
  // Clean();
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
