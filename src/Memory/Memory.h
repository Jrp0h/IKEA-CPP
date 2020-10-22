#pragma once

#include <array>

class Memory {
public:
  Memory();
  Memory(int value);
  Memory(std::array<bool, 16> value);

  void SetValue(int value);
  void SetValue(std::array<bool, 16> value);

  int GetValue();

private:
  void ResetValue();

private:
  std::array<bool, 16> m_Data;
};
