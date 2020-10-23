# Readme aka notes for self

## Value types

VAR_VALUE ($) = the value at the memory address the var is pointing to
VAR (&) = the memory address the var is pointing to
DIRECT (\#) = Index of memory
PLAIN () = Normal number
STR = Text

## Instructions

### Declaration

Declare section

```bash
SEC [STR]:
```

Declare function

```bash
FUN [STR]:
```

> Requires EFUN when the function is done

### Numbers

Increment number by one

```bash
INC [$VAR_VALUE|&VAR|#DIRECT]
```

Decrement number by one

```bash
DEC [$VAR_VALUE|&VAR|#DIRECT]
```

#### Bitwise

AND

arg1 = arg2 & arg3

```bash
AND [$VAR_VALUE|&VAR|#DIRECT],[$VAR_VALUE|&VAR|#DIRECT|PLAIN],[$VAR_VALUE|&VAR|#DIRECT|PLAIN]
```

arg1 = arg1 & arg2

```bash
AND [$VAR_VALUE|&VAR|#DIRECT],[$VAR_VALUE|&VAR|#DIRECT|PLAIN],[$VAR_VALUE|&VAR|#DIRECT|PLAIN]
```

OR

arg1 = arg2 | arg3

```bash
OR [$VAR_VALUE|&VAR|#DIRECT],[$VAR_VALUE|&VAR|#DIRECT|PLAIN],[$VAR_VALUE|&VAR|#DIRECT|PLAIN]
```

arg1 = arg1 | arg2

```bash
OR [$VAR_VALUE|&VAR|#DIRECT],[$VAR_VALUE|&VAR|#DIRECT|PLAIN],[$VAR_VALUE|&VAR|#DIRECT|PLAIN]
```

XOR

arg1 = arg2 ^ arg3

```bash
XOR [$VAR_VALUE|&VAR|#DIRECT],[$VAR_VALUE|&VAR|#DIRECT|PLAIN],[$VAR_VALUE|&VAR|#DIRECT|PLAIN]
```

arg1 = arg1 | arg2

```bash
XOR [$VAR_VALUE|&VAR|#DIRECT],[$VAR_VALUE|&VAR|#DIRECT|PLAIN],[$VAR_VALUE|&VAR|#DIRECT|PLAIN]
```

### Flow Control

Jump to section if value is 0(zero)

```bash
JMPZ [$VAR_VALUE|&VAR|#DIRECT],[SEC_STR]
```

Jump to section if value is 1(one)

```bash
JMPO [$VAR_VALUE|&VAR|#DIRECT],[SEC_STR]
```

Jump to section if value is \<2nd param\>

```bash
JMPT [$VAR_VALUE|&VAR|#DIRECT|PLAIN],[$VAR_VALUE|&VAR|#DIRECT|PLAIN],[SEC_STR]
```

Jump to section if value is NOT \<2nd param\>

```bash
JMPF [$VAR_VALUE|&VAR|#DIRECT|PLAIN],[$VAR_VALUE|&VAR|#DIRECT|PLAIN],[SEC_STR]
```

### Other

Jump to section if value is 0(zero)

```bash
JMP [SEC_STR]
```

Set data at memory address

```bash
MOV [$VAR_VALUE|&VAR|#DIRECT],[$VAR_VALUE|&VAR|#DIRECT|PLAIN]
```

Invoke Function

```bash
CALL [FUN_STR]
```

Return from Function

```bash
RET
```

Assign variable

```bash
VAR [STR],[$VAR_VALUE|&VAR|#DIRECT|PLAIN]
```

### Misc

Print text

```bash
PRNT [STR]
```

Print All variables

```bash
PRNTV
```

Print Memory

```bash
PRNTM
```

## Examples

Hello World

```c++
#include <iostream>

int main() {
  std::cout << "Hello World" << std::endl;
}
```

```bash
PRNT Hello World
```

Function that print hello

```c++
#include <iostream>

void sayHello() {
  std::cout << "hello" << std::endl;
}

int main() {
  sayHello();
}
```

```bash
CALL sayHello

FUN sayHello:
  PRNT hello
EFUN
```

Variables

```c++
#include <iostream>

int main() {
  // This simulates the memory used
  // in IKEA
  int mem1 = 19;

  int* age = &mem1;
  *age++;

  std::cout << age << std::endl;
  std::cout << *age << std::endl;
}
```

```bash
; Memory addressed are not real addresses
; they are synthetic

MOV #1,19

VAR age,#1
INC $age

PRNT &age
PRNT $age
```

If, else if, else

```c++
#include <iostream>

int main() {
  int mem1 = 17;
  int* age = &mem1;

  if(*age == 18)
  {
    std::cout << "You can drink!" << std::endl;
  }
  else if(*age == 20)
  {
    std::cout << "You are getting old" << std::endl;
  }
  else
  {
    std::cout << "greater than and less than?" << std::endl;
  }

  std::cout << "after comparisons" << std::endl;
}
```

```bash
MOV #1,17

VAR age,#1

JMPT $age,18,eighteen
JMPT $age,20,twenty
JMP neither

SEC eighteen:
  PRNT You can drink!
  JMP ac
SEC twenty:
  PRNT You are getting old
  JMP ac
SEC neither:
  PRNT greater than and less than
  JMP ac

SEC ac:
  PRNT after comparisons
```

While loop

```c++
#include <iostream>

int main() {
  int mem1 = 5;

  int* i = &mem1;
  
  while(*i != 0)
  {
    std::cout << *i << std::endl;
    (*i)--;
  }

  std::cout << "Out of the Loop" << std::endl;
}
```

```bash
MOV #1,5

VAR i,#1

JMPF $i,0,loop
JMP after

SEC loop:
  PRNT $i
  DEC $i
  JMPF $i,0,loop
  JMP after

SEC after:
  PRNT Out of the Loop
```

Fibonacci forloop

```c++
// From
// https://www.programiz.com/cpp-programming/examples/fibonacci-series
#include <iostream>

int main() {
  int mem1 = 0;
  int mem2 = 0;
  int mem3 = 0;
  int mem4 = 0;
  int mem5 = 0;

  int* n = &mem1;
  int* t1 = &mem2;
  int* t2 = &mem3;
  int* tn = &mem4;
  int* i = &mem5;

  *t2 = 1;
  *i = 1;
  
  while(*i != n)
  {
    if(*i == 1)
    {
      std::cout << *t1 << std::endl;
      continue;
    }
    if(*i == 2)
    {
      std::cout << *t2 << std::endl;
      continue;
    }

    *nt = *t1 + *t2;
    *t1 = *t2;
    *t2 = *nt;

    std::cout << *nt << std::endl;

    (*i)++;
  }
}
```

```bash
VAR n,#1
VAR t1,#2
VAR t2,#3
VAR nt,#4
VAR i,#5

MOV &n,10
MOV &t2,1

SEC loop:
   JMPZ $i,isOne
   JMPO $i,isTwo

   ADD &nt,$t1,$t2

   PRNT $nt

   MOV &t1,$t2
   MOV &t2,$nt

   JMP validate

SEC isOne:
   PRNT $t1
   JMP validate

SEC isTwo:
   PRNT $t2
   JMP validate

SEC validate:
   INC $i

   JMPF $i,$n,loop
```

Fibonacci function

```c++
// From
// https://www.programiz.com/cpp-programming/examples/fibonacci-series
#include <iostream>

void fibonacci()
{
  int mem1 = 0;
  int mem2 = 0;
  int mem3 = 0;
  int mem4 = 0;
  int mem5 = 0;

  int* n = &mem1;
  int* t1 = &mem2;
  int* t2 = &mem3;
  int* tn = &mem4;
  int* i = &mem5;

  *t2 = 1;
  *i = 1;
  
  while(*i != n)
  {
    if(*i == 1)
    {
      std::cout << *t1 << std::endl;
      continue;
    }
    if(*i == 2)
    {
      std::cout << *t2 << std::endl;
      continue;
    }

    *nt = *t1 + *t2;
    *t1 = *t2;
    *t2 = *nt;

    std::cout << *nt << std::endl;

    (*i)++;
  }
}

int main() {
  fibonacci();
}
```

```bash
CALL fibonnaci

FUN fibonnaci:
   VAR n,#1
   VAR t1,#2
   VAR t2,#3
   VAR nt,#4
   VAR i,#5

   MOV &n,10
   MOV &t2,1

   SEC loop:
      JMPZ $i,isOne
      JMPO $i,isTwo

      ADD &nt,$t1,$t2

      PRNT $nt

      MOV &t1,$t2
      MOV &t2,$nt

      JMP validate

   SEC isOne:
      PRNT $t1
      JMP validate

   SEC isTwo:
      PRNT $t2
      JMP validate

   SEC validate:
      INC $i
      JMPF $i,$n,loop
      RET
EFUN
```
