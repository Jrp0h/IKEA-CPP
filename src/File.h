#pragma once

#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Str.h"
#include "Exception/FileImportException.h"

using namespace IKEA::Exception;

namespace IKEA {

   class File {
      public:
         File(const std::string &path) {
            std::ifstream file(std::filesystem::current_path().concat("/" + path).c_str());

            // Try importing file 
            if (!file.is_open())
               throw FileImportException("File Not Found. Failed loading file: " + path);
        
            m_Lines = std::vector<std::string>();
        
            std::string line;
            
            // Add all line to a vector of lines
            while (!file.eof()) {
               std::getline(file, line);
        
               m_Lines.push_back(Str::Trim(line));
            }
        
            m_Path = path;
         }
        
         std::string GetPath() { return m_Path; }
         std::vector<std::string> GetLines() { return m_Lines; }

      private:
         std::string m_Path;
         std::vector<std::string> m_Lines;
      };
}
