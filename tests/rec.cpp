#include <iostream>

int fib(int x){
   if(x == 0 || x == 1)
      return x;
   else
      return fib(x - 1) + fib(x - 2);
}

int main()
{
   for(int i = 0; i < 15; i++)
   {
      std::cout << fib(i) << std::endl;
   }
}
