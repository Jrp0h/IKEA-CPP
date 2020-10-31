#include <iostream>
#include <filesystem>
#include <stdlib.h>
#include <unistd.h>

#include "Program.h"
#include "Callstack.h"
#include "Memory/Register.h"

void printHelp();

int main(int argc, char** argv)
{
   int c;

   while((c = getopt(argc, argv, "h")) != EOF)
   {
      if(c == 'h')
         printHelp();
   }

   if(argc == 1)
   {
      std::cout << "Missing file" << std::endl;
      printHelp();
   }

   std::string file = argv[1];

#ifdef IKEA_VERBOSE
   std::cout << "IKEA runing in ";
#ifdef IKEA_DEBUG
   std::cout << "DEBUG MODE" << std::endl;
   std::cout << "Loading file: " << file << std::endl << std::endl;
#endif
#ifdef IKEA_RELEASE
   std::cout << "RELEASE MODE"<< std::endl; 
#endif
#endif

   IKEA::Program::Load(file);
   IKEA::Program::Run();
}

void printHelp() {
   std::cout << "Usage: IKEA file [options]" << std::endl
      << "Options:" << std::endl
      << "\t-h\t\tDisplay this message" << std::endl;

   exit(EXIT_SUCCESS);
}
