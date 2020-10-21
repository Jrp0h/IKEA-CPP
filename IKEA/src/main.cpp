#include <iostream>
#include <filesystem>

#include "Program.h"

int main()
{
   std::cout << "Hello World" << std::endl;
   Program::Load("test.ikea");
}
