#pragma once

#include <array>

namespace IKEA::Memory {
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
      std::string ToHexString();

      static Memory FromBinaryString(const std::string& string);
      static Memory FromHexString(const std::string& string);

      bool& operator[](const int i);

      static Memory TwoCompliment(Memory& mem);

      Memory RotateLeft(int amount);
      Memory RotateRight(int amount);

      Memory ShiftLeft(int amount);
      Memory ShiftRight(int amount);


      static Memory Add(Memory& mem1, Memory& mem2);
      static Memory Subtract(Memory& mem1, Memory& mem2);
      static bool Equal(Memory& mem1, Memory& mem2);

      static Memory AND(Memory& mem1, Memory& mem2);
      static Memory OR(Memory& mem1, Memory& mem2);
      static Memory XOR(Memory& mem1, Memory& mem2);
      static Memory NOT(Memory& mem1);

      static bool GreaterThan(Memory& mem1, Memory& mem2);
      static bool LessThan(Memory& mem1, Memory& mem2);

      Memory NOT();

      Memory operator+(Memory& other);
      Memory operator+(int other);

      Memory operator-(Memory& other);
      Memory operator-(int other);

      bool operator==(Memory& other);
      bool operator!=(Memory& other);

      bool operator>(Memory& other);
      bool operator<(Memory& other);

      bool operator>=(Memory& other);
      bool operator<=(Memory& other);

      Memory operator&(Memory& other);
      Memory operator&(int other);

      Memory operator|(Memory& other);
      Memory operator|(int other);

      Memory operator^(Memory& other);
      Memory operator^(int other);

    private:
      void ResetValue();

    private:
      bool m_Data[16];

      inline static char m_HexChars[17] = "0123456789ABCDEF";
  };
}
