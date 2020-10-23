#pragma once

#include <array>

class Memory {
public:
  Memory();
  Memory(int value);
  Memory(bool value[16]);

  void SetValue(int value);
  void SetValue(bool value[16]);

  int GetValue();

  std::string ToBinaryString();

private:
  void ResetValue();

private:
  bool m_Data[16];
};
