#pragma once

#include <vector>
#include <string>

#include "File.h"
#include "Lineinfo.h"

class ProgramFiles {
  public:
   static void Load(const std::string &file);

   static bool Import();
   static void Clean();

   static std::string LineinfoToString(Lineinfo fileinfo);
   static std::string LineinfoToString(int realLine);
   static Lineinfo LineinfoFromRealline(int realLine);

   static void InsertLines(int start, std::vector<std::string> lines, int newFileId);

   static bool EndOfProgram(int linenr);
   static std::string GetRealLine(int linenr);

   static std::vector<std::string> GetAllLines();
private:
   inline static std::vector<File> m_Files;
   inline static std::vector<Lineinfo> m_LineInfos;
   inline static std::vector<std::string> m_RealLines;
};
