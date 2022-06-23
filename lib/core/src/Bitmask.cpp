#include <iostream>

#include <utility>

#include "Bitmask.hpp"

Bitmask::Bitmask() : m_bits(0) {}

Bitmask::Bitmask(uint32_t bits) : m_bits(bits) {}

Bitmask::~Bitmask() {}

Bitmask::Bitmask(const Bitmask &other)
  : Bitmask(other.m_bits) {}

Bitmask::Bitmask(Bitmask &&other) noexcept
  : m_bits(std::exchange(other.m_bits, 0)) {}

Bitmask &Bitmask::operator=(const Bitmask &other)
{
  m_bits = other.m_bits;

  return *this;
}

Bitmask &Bitmask::operator=(Bitmask &&other) noexcept
{
  m_bits = std::exchange(other.m_bits, 0);

  return *this;
}

uint32_t Bitmask::GetMask() const
{
  return m_bits;
}

bool Bitmask::GetBit(int pos) const
{
  return (m_bits & (1 << pos)) != 0;
}

void Bitmask::SetBit(int pos, bool on)
{
  if (on)
  {
    SetBit(pos);
  }
  else
  {
    ClearBit(pos);
  }
}

void Bitmask::SetBit(int pos)
{
  m_bits = m_bits | 1 << pos;
}

void Bitmask::ClearBit(int pos)
{
  m_bits = m_bits & ~(1 << pos);
}

void Bitmask::Clear()
{
  m_bits = 0;
}
