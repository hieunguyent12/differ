#include <iostream>
#include "utils.h"

std::string utils::repeat(char c, int times)
{
  std::string s = "";

  for (auto i = 0; i < times; i++)
  {
    s += c;
  }

  return s;
}