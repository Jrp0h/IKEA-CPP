#pragma once

#include <string>
#include <vector>

#include "File.h"
#include "Lineinfo.h"

class Program {
public:
   static void Load(const std::string &file);
   static void Run();

   static std::string LineinfoToString(Lineinfo fileinfo);
   static Lineinfo LineinfoFromRealline(int realLine);

private:
   static void Import();
   static void Clean();
   static void FindSegments();

   static void InsertLines(int start, std::vector<std::string> lines, int newFileId);

private:
  // Move to map?
   inline static std::vector<Lineinfo> m_LineInfos;
   inline static std::vector<std::string> m_RealLines;
   inline static std::vector<File> m_Files;
};
