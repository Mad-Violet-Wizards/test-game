
#pragma once

struct ComponentPairHash
{
  template<typename T>
  size_t operator()(T t) const
  {
    size_t x = t.first -> owner -> instanceID -> GetID();
    size_t y = t.second -> owner -> instanceID -> GetID();

    return (x >= y) ? (x * x + x + y) : (y * y + y * x);
  }
};