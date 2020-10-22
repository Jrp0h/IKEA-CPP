#include "ProgramFiles.h"

#include "Str.h"

void ProgramFiles::Load(const std::string &path) {
  File f(path);
  m_Files.push_back(f);

  m_LineInfos = std::vector<Lineinfo>();
  m_RealLines = f.GetLines();

  for (int i = 0; i < f.GetLines().size(); i++) {
    m_LineInfos.push_back(Lineinfo(0, i + 1, i));
  }

  while(Import());
  Clean();

// #if IKEA_DEBUG
  // for(auto line : m_RealLines)
  // {
    // std::cout << line << std::endl;
  // }
// #endif
}

bool ProgramFiles::Import() {

  for (int i = 0; i < m_RealLines.size(); i++) {
    if (m_RealLines[i].find("IMP") == 0) {
      std::string path = m_RealLines[i].substr(m_RealLines[i].find(" ") + 1);
      Str::Trim(path);

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

      return true;
    }
  }

  return false;
}

void ProgramFiles::Clean() {

  for(int i = 0; i < m_RealLines.size(); i++)
  {
    auto commentPos = m_RealLines[i].find(";");

    if(commentPos != std::string::npos)
      m_RealLines[i] = m_RealLines[i].substr(0, commentPos);

    Str::Trim(m_RealLines[i]);
  }
}

void ProgramFiles::InsertLines(int start, std::vector<std::string> lines,
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

  for(int i = start + 1; i < m_LineInfos.size(); i++)
  {
    tmpLineInfos[i + lines.size() - 1] = m_LineInfos[i];
    tmpLineInfos[i + lines.size() - 1].m_RealLine += lines.size() - 1;
  }

  for(int i = start + 1; i < m_RealLines.size(); i++)
  {
    tmpRealLines[i + lines.size() - 1] = m_RealLines[i];
  }
  

  m_RealLines = tmpRealLines;
  m_LineInfos = tmpLineInfos;
}

std::string ProgramFiles::LineinfoToString(Lineinfo lineinfo) {
  std::stringstream ss;
  ss << std::endl << "File: " << m_Files[lineinfo.m_FileIndex].GetName() << " at line "
     << lineinfo.m_FileLine << std::endl;

    ss << lineinfo.m_FileLine << " | " << m_RealLines[lineinfo.m_RealLine] << std::endl;

  return ss.str();
}

std::string ProgramFiles::LineinfoToString(int realLine) {
  return LineinfoToString(LineinfoFromRealline(realLine));
}

Lineinfo ProgramFiles::LineinfoFromRealline(int realLine) {

  for (int i = 0; i < m_LineInfos.size(); i++) {
    if (m_LineInfos[i].m_RealLine == realLine)
      return m_LineInfos[i];
  }

  throw std::runtime_error("Failed finding lineinfo from real line: " +
                           std::to_string(realLine));
}

bool ProgramFiles::EndOfProgram(int linenr)
{
  return linenr >= m_RealLines.size();
}

std::string ProgramFiles::GetRealLine(int linenr) {
  
  // TODO: Custom exceptions
  if(linenr >= m_RealLines.size())
    throw std::runtime_error("End of Program");
    
  return m_RealLines[linenr];
}

std::vector<std::string> ProgramFiles::GetAllLines() {
  return m_RealLines;
}
