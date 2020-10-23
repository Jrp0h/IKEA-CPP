#include <math.h>
#include <iostream>
#include <sstream>

#include "Memory.h"

Memory::Memory() {
  ResetValue();
}

Memory::Memory(int value){
  SetValue(value);
}

Memory::Memory(bool value[16]) {
  SetValue(value);
}

void Memory::SetValue(int value){
  // std::cout << "Value: " << value << std::endl;
  bool isNegative = value < 0;
  
  if(isNegative)
    value *= -1;

  ResetValue();

  for(int i = 0; value != 0 && i < 16 - 1; i++)
  {
    m_Data[16 - 1 - i] = (value % 2) == 1;
    value = (int)floor((float)value / 2.0f);
  }

  // std::cout << "sum: " << GetValue() << std::endl;
}

void Memory::SetValue(bool value[16]) {
  for(int i = 0; i < 16; i++)
    m_Data[i] = value[i];
}

int Memory::GetValue() {

  int sum = 0;

  for(int i = 0; i < 16; i++)
  {
    sum += pow(2, i) * m_Data[16 - 1 - i];
  }

  return sum;
}

void Memory::ResetValue() {
  for(int i = 0; i < 16; i++)
  {
    m_Data[i] = false;
  }
}

std::string Memory::ToBinaryString() {
  std::stringstream ss;
  
  for(int i = 0; i < 16; i++)
  {
    ss << m_Data[i];
  }

  return ss.str();
}
