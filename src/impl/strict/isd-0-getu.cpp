#include "../../base.hpp"

#include <cctype>

inline static u64 isd_0_getu(const char *&p) {
  char c = *p++;
  while (!std::isdigit(c))
    c = *p++;
  u64 x = c - '0';
  for (c = *p++; std::isdigit(c); c = *p++)
    x = x * 10 + c - '0';
  return x;
}

#ifndef ALGO_VERIFY

#include "../bench-1.hpp"

extern "C" u64 bm_isd_0_getu(const char *p) {
  return _bm<isd_0_getu>(p);
}

#else

#include "../strict-test-1.hpp"

int main() {
  _test_strict_getu<isd_0_getu>();
}

#endif
