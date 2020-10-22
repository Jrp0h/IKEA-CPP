#pragma once

#include <vector>

#include "Lineinfo.h"

class Callstack {
   public:
      static void Push(int line) { 
         m_LastLines.push_back(line);
      }

      static int Peek() { 
         return m_LastLines[m_LastLines.size() - 1];
      }

      static int Pop() { 
         auto line = m_LastLines[m_LastLines.size() - 1];
         m_LastLines.pop_back();
         return line;
      }

      static std::vector<int> GetStack() {
         return m_LastLines;
      }

   private:
      inline static std::vector<int> m_LastLines;
};
