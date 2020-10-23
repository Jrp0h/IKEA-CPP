#include <iostream>
#include <filesystem>

#include "Program.h"
#include "Memory/Register.h"

int main(int argc, char** argv)
{
#ifdef IKEA_VERBOSE
   std::cout << "IKEA runing in ";
#ifdef IKEA_DEBUG
   std::cout << "DEBUG MODE" << std::endl;
#endif
#ifdef IKEA_RELEASE
   std::cout << "RELEASE MODE"<< std::endl; 
#endif
#endif

   std::string file = "code.ikea";

   if(argc > 1)
      file = argv[1];

#ifdef IKEA_DEBUG
   std::cout << "Loading file: " << file << std::endl << std::endl;
#endif

   IKEA::Program::Load(file);
   IKEA::Program::Run();
   IKEA::Memory::Register::PrintVars();
}
