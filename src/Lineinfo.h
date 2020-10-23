#pragma once

namespace IKEA {
class Lineinfo {
public:
   Lineinfo(int fileIndex, int fileLine, int realLine) 
      : m_FileIndex(fileIndex), m_FileLine(fileLine), m_RealLine(realLine) {}

   Lineinfo() 
      : m_FileIndex(0), m_FileLine(0), m_RealLine(0) {}

public:
   int m_FileIndex;
   int m_FileLine;
   int m_RealLine;
};
}
