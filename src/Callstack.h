#pragma once

#include <vector>

#include "Lineinfo.h"
#include "ProgramFiles.h"
#include "ProgramState.h"

class Callstack {
   public:
      static void Push(int line) { 
         m_LastLines.push_back(line);
      }

      static int Peek() { 
         if(m_LastLines.size() <= 0)
            return -1;

         return m_LastLines[m_LastLines.size() - 1];
      }

      static int Pop() { 
         if(m_LastLines.size() <= 0)
            throw std::runtime_error("Can't return from base. " + ProgramFiles::LineinfoToString(ProgramState::GetCurrentLine()));

         int line = m_LastLines[m_LastLines.size() - 1];
         m_LastLines.pop_back();

         return line;
      }

      static std::vector<int> GetStack() {
         return m_LastLines;
      }

   private:
      inline static std::vector<int> m_LastLines;
};
