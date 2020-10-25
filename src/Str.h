#pragma once

#include <string>
#include <algorithm>

namespace IKEA {
  class Str {
  public:
    static std::string& Trim(std::string& s)
    {
      // Trim begining
      s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
      }));

      // Trim end
      s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
      }).base(), s.end());

      return s;
    }

    static std::string& ToUpper(std::string& s)
    {
      std::for_each(s.begin(), s.end(), [](char & c) {
        c = ::toupper(c);
      });

      return s;
    }

    static std::string& ToLower(std::string& s)
    {
      std::for_each(s.begin(), s.end(), [](char & c) {
        c = ::tolower(c);
      });

      return s;
    }
  };
}
