#pragma once

#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class File {
public:
   File(const std::string &path) {
      std::ifstream file(std::filesystem::current_path().concat("/" + path).c_str());
  
      if (!file.is_open())
        throw std::runtime_error(std::string("Failed loading file: " + path).c_str());
  
      m_Lines = std::vector<std::string>();
  
      std::string line;
  
      while (!file.eof()) {
         std::getline(file, line);
  
         // if (line == "")
           // break;
  
         m_Lines.push_back(line);
      }
  
      m_Name = path;
   }
  
   std::string GetName() { return m_Name; }
   std::vector<std::string> GetLines() { return m_Lines; }

private:
   std::string m_Name;
   std::vector<std::string> m_Lines;
};
