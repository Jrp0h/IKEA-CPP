#pragma once

#include <string>
#include <vector>

#include "File.h"
#include "Lineinfo.h"
#include "Instruction/Instruction.h"

class Program {
public:
   static void Load(const std::string &file);
   static void Run();

   static std::string LineinfoToString(Lineinfo fileinfo);
   static Lineinfo LineinfoFromRealline(int realLine);

   static void SetNextLine(int line);
   static int GetNextLine();

private:
   static void Import();
   static void Clean();
   static void FindSegments();
   static void InitInstructions();

   static void InsertLines(int start, std::vector<std::string> lines, int newFileId);


   static void ReadNextLine();
private:
  // Move to map?
   inline static std::vector<Lineinfo> m_LineInfos;
   inline static std::vector<std::string> m_RealLines;
   inline static std::vector<File> m_Files;
   inline static std::vector<Instruction> m_Instructions;

   inline static int m_NextLine = 0;
   inline static int m_CurrentLine = 0;
   inline static bool m_IsInFunction = false;

};
