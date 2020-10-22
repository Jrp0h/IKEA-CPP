#include <iostream>
#include <filesystem>

#include "Program.h"

int main()
{

#ifdef IKEA_DEBUG
   std::cout << "DEBUG" << std::endl;
#endif
#ifdef IKEA_RELEASE
   std::cout << "RELEASE" << std::endl;
#endif

   Program::Load("test.ikea");
}
