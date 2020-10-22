#include <math.h>
#include <iostream>

#include "Memory.h"

Memory::Memory() {
  ResetValue();
}

Memory::Memory(int value){
  SetValue(value);
}

Memory::Memory(std::array<bool, 16> value) {
  SetValue(value);
}

void Memory::SetValue(int value){
  bool isNegative = value < 0;
  
  if(isNegative)
    value *= -1;

  for(int i = 0; value != 0 && i < m_Data.size() - 1; i++)
  {
    m_Data[m_Data.size() - 1 - i] = (value % 2) == 1;
    value = (int)floor((float)value / 2.0f);
  }
}

void Memory::SetValue(std::array<bool, 16> value) {
    m_Data = value;
}

int Memory::GetValue() {

  int sum = 0;

  for(int i = 0; i < m_Data.size(); i++)
  {
    sum += pow(2, i) * m_Data[m_Data.size() - 1 - i];
  }

  return sum;
}

void Memory::ResetValue() {
  for(int i = 0; i < m_Data.size(); i++)
  {
    m_Data[i] = false;
  }
}
