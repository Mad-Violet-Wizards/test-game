#pragma once

#include <stdint.h>

class Bitmask
{

public:

  Bitmask();
  Bitmask(uint32_t bits);
  ~Bitmask();

  Bitmask(const Bitmask &other);
  Bitmask(Bitmask &&other) noexcept;

  Bitmask &operator=(const Bitmask &other);
  Bitmask &operator=(Bitmask &&other) noexcept;

  uint32_t GetMask() const;

  bool GetBit(int pos) const;
  void SetBit(int pos, bool on);

  void SetBit(int pos);
  void ClearBit(int pos);

  void Clear();

private:

  uint32_t m_bits;

};
