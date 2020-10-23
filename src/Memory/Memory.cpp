#include <math.h>
#include <iostream>
#include <sstream>
#include <math.h>

#include "Memory.h"

namespace IKEA::Memory {
  Memory::Memory() {
    ResetValue();
  }

  Memory::Memory(int value){
    SetValue(value);
  }

  Memory::Memory(bool value[16]) {
    SetValue(value);
  }

  Memory::Memory(bool value) {
    if(value)
      SetValue(1);
    else
      SetValue(0);
  }

  void Memory::SetValue(int value){
    bool isNegative = value < 0;
    
    if(isNegative)
      value *= -1;

    ResetValue();

    for(int i = 0; value != 0 && i < 16 - 1; i++)
    {
      m_Data[16 - 1 - i] = (value % 2) == 1;
      value = (int)floor((float)value / 2.0f);
    }
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

    ss << "0b";
    
    for(int i = 0; i < 16; i++)
    {
      ss << m_Data[i];
    }

    return ss.str();
  }

  std::string Memory::ToHexString() {
    std::stringstream ss;

    ss << "0x";
    
    for(int i = 0; i < 4; i++)
    {
      int c = 0;

      // TODO: FIX THIS SHIT
      // IT IS NOT WORKING AS IT SHOULD!
      for(int j = 0; j < 4; j++)
      {
        c += pow(2, j) * m_Data[i * 4 + j];
      }
      ss << m_HexChars[c];
    }

    return ss.str();
  }

  bool& Memory::operator[](const int i)
  {
    if(i > 15)
      throw std::runtime_error("Can't access bit " + std::to_string(i));

    return m_Data[i];
  }

  Memory Memory::TwoCompliment(Memory &mem) {
    for(int i = 0; i < 16; i++) {
      mem[i] = !mem[i];
    }

    Memory one(1);

    return Add(mem, one);
  }

  Memory Memory::RotateLeft(int amount) {

    for(int i = 0; i < amount; i++)
    {
      bool tmp = this->m_Data[0];
      for(int j = 15; j >= 0; j -= 2){
        bool tmp2 = this->m_Data[j];
        this->m_Data[j] = tmp;
        tmp = this->m_Data[j - 1];
        this->m_Data[j - 1] = tmp2;
      }
    }

    return *this;

  }

  Memory Memory::RotateRight(int amount) {

    for(int i = 0; i < amount; i++)
    {
      bool tmp = this->m_Data[16 - 1];
      for(int j = 0; j < 16; j += 2){
        bool tmp2 = this->m_Data[j];
        this->m_Data[j] = tmp;
        tmp = this->m_Data[j + 1];
        this->m_Data[j + 1] = tmp2;
      }
    }

    return *this;
  }

  Memory Memory::ShiftLeft(int amount) {

    for(int i = 0; i < amount; i++)
    {
      for(int j = 1; j < 16; j++){
        this->m_Data[j - 1] = this->m_Data[i];
      }
    }
    this->m_Data[0] = false;

    return *this;

  }

  Memory Memory::ShiftRight(int amount) {

    for(int i = 0; i < amount; i++)
    {
      for(int j = 14; j >= 0; j--){
        this->m_Data[j - 1] = this->m_Data[i];
      }
    }
    this->m_Data[15] = false;

    return *this;
  }

  Memory Memory::Subtract(Memory& mem1, Memory& mem2) {
    
    mem2 = TwoCompliment(mem2);
    Memory result = Add(mem1, mem2);
    mem2 = TwoCompliment(mem2);

    return result;
  }

  Memory Memory::Add(Memory& mem1, Memory& mem2) {
    Memory res;

    int carry = 0;
    res.ResetValue();

    for(int i = 15; i >= 0; i--)
    {
        int sum = (int)mem1[i] + (int)mem2[i];

        if(carry > 0) {
          sum++;
          carry--;
        }

        if(sum == 2) {
          carry++;
        } else {
          if(sum == 3) {
            carry++;
          }
          res[i] = sum == 1 || sum == 3;
        }
    }

    return res;
  }

  bool Memory::Equal(Memory& mem1, Memory& mem2){
    for(int i = 0; i < 16; i++) {
      if(mem1[i] != mem2[i])
        return false;
    }

    return true;
  }

  Memory Memory::AND(Memory& mem1, Memory& mem2){
    Memory res;

    for(int i = 0; i < 16; i++) {
      res[i] = mem1[i] && mem2[i];
    }

    return res;
  }

  Memory Memory::OR(Memory& mem1, Memory& mem2){
    Memory res;

    for(int i = 0; i < 16; i++) {
      res[i] = mem1[i] || mem2[i];
    }

    return res;
  }

  Memory Memory::XOR(Memory& mem1, Memory& mem2) {
    Memory res;

    for(int i = 0; i < 16; i++) {
      res[i] = !(mem1[i] == mem2[i]);
    }

    return res;
  }

  Memory Memory::operator+(Memory& other) {
    return Add(*this, other);
  }

  Memory Memory::operator+(int other) {
    Memory mem(other);
    return Add(*this, mem);
  }

  Memory Memory::operator-(Memory& other) {
    return Subtract(*this, other);
  }

  Memory Memory::operator-(int other) {
    Memory mem(other);
    return Subtract(*this, mem);
  }

  bool Memory::operator==(Memory& other) {
    return Equal(*this, other);
  }

  bool Memory::operator!=(Memory& other) {
    return !Equal(*this, other);
  }

  Memory Memory::operator&(Memory& other){
    return AND(*this, other);
  }

  Memory Memory::operator&(int other) {
    Memory mem(other);
    return AND(*this, mem);
  }

  Memory Memory::operator|(Memory& other){
    return OR(*this, other);
  }

  Memory Memory::operator|(int other) {
    Memory mem(other);
    return OR(*this, mem);
  }

  Memory Memory::operator^(Memory& other){
    return OR(*this, other);
  }

  Memory Memory::operator^(int other) {
    Memory mem(other);
    return OR(*this, mem);
  }
}
