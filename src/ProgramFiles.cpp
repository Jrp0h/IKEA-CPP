#include "ProgramFiles.h"

#include "Str.h"

#include "Exception/InvalidArgumentCountException.h"
#include "Exception/CircularImportException.h"

using namespace IKEA::Exception;

namespace IKEA {
  void ProgramFiles::Load(const std::string &path) {
    // Load the main file and create new realline and lineinfo
    File f(path);
    m_Files.push_back(f);

    m_LineInfos = std::vector<Lineinfo>();
    m_RealLines = f.GetLines();

    for (int i = 0; i < f.GetLines().size(); i++) {
      m_LineInfos.push_back(Lineinfo(0, i + 1, i));
    }

    // Keep importing untill there are no imports left
    while(Import());
    Clean();
  }

  bool ProgramFiles::Import() {

    for (int i = 0; i < m_RealLines.size(); i++) {
      if (m_RealLines[i].find("IMP") == 0) {
        std::string path = m_RealLines[i].substr(m_RealLines[i].find(" ") + 1);
        Str::Trim(path);

        // check if it's missing arguments
        // for some reason when it cant find space
        // it just gets the whole string
        if (path == "IMP" || path == "")
          throw InvalidArgumentCountException("Missing arguments.", LineinfoFromRealline(i));

        // Remove opening "
        if (path.find("\"") == 0)
          path = path.erase(0, 1);

        // Remove closeing "
        if (path.find("\"") == path.length() - 1)
          path = path.erase(path.length() - 1);

        for(auto file : m_Files)
        {
          // Check if file is not already imported
          if(file.GetPath() == path) {
            throw CircularImportException("Circular import not allowed. " + path + " is already imported.", LineinfoFromRealline(i));
            std::cout << "Circular" << std::endl;
          }
        }
        File f(path);

        InsertLines(i, f.GetLines(), m_Files.size());

        return true;
      }
    }

    return false;
  }

  void ProgramFiles::Clean() {

    // Remove all comments
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

    // Create the new objects
    std::vector<std::string> tmpRealLines;
    std::vector<Lineinfo> tmpLineInfos;

    // resize to correct size 
    tmpRealLines.resize(m_RealLines.size() + lines.size() - 1);
    tmpLineInfos.resize(m_LineInfos.size() + lines.size() - 1);

    // Add every line and lineinfo
    // before the start, which should not change place
    for (int i = 0; i < start; i++) {
      tmpRealLines[i] = m_RealLines[i];
      tmpLineInfos[i] = m_LineInfos[i];
    }

    // Add all the newly imported lines
    for (int i = 0; i < lines.size(); i++) {
      tmpRealLines[i + start] = lines[i];
      tmpLineInfos[i + start] = Lineinfo(newFileId, i + 1, i + start);
    }

    // Add all the old lines which come after start
    // and add the to the new vectors
    for(int i = start + 1; i < m_LineInfos.size(); i++)
    {
      tmpLineInfos[i + lines.size() - 1] = m_LineInfos[i];
      tmpLineInfos[i + lines.size() - 1].m_RealLine += lines.size() - 1;
    }

    // Add all the old lines which come after start
    // and add the to the new vectors
    for(int i = start + 1; i < m_RealLines.size(); i++)
    {
      tmpRealLines[i + lines.size() - 1] = m_RealLines[i];
    }
    
    // Assign the new vectors
    m_RealLines = tmpRealLines;
    m_LineInfos = tmpLineInfos;
  }

  std::string ProgramFiles::LineinfoToString(Lineinfo lineinfo) {
    std::stringstream ss;
    ss << std::endl << std::endl << "File: " << m_Files[lineinfo.m_FileIndex].GetPath() << " at line "
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
    
    if(linenr >= m_RealLines.size())
      throw std::runtime_error("End of Program");
      
    return m_RealLines[linenr];
  }

  std::vector<std::string> ProgramFiles::GetAllLines() {
    return m_RealLines;
  }
}
