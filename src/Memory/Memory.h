#pragma once

#include <array>

class Memory {
public:
  Memory();
  Memory(int value);
  Memory(bool value[16]);
  Memory(bool value);

  void SetValue(int value);
  void SetValue(bool value[16]);

  int GetValue();

  std::string ToBinaryString();

  bool& operator[](const int i);

  Memory TwoCompliment(Memory& mem);

  Memory RotateLeft(int amount);
  Memory RotateRight(int amount);

  Memory ShiftLeft(int amount);
  Memory ShiftRight(int amount);

  Memory Add(Memory& mem1, Memory& mem2);
  Memory Subtract(Memory& mem1, Memory& mem2);
  bool Equal(Memory& mem1, Memory& mem2);

  Memory AND(Memory& mem1, Memory& mem2);
  Memory OR(Memory& mem1, Memory& mem2);
  Memory XOR(Memory& mem1, Memory& mem2);

  Memory operator+(Memory& other);
  Memory operator+(int other);
  Memory operator-(Memory& other);
  Memory operator-(int other);
  bool operator==(Memory& other);
  bool operator!=(Memory& other);

private:
  void ResetValue();

private:
  bool m_Data[16];
};
