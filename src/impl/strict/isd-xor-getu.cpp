#include "../../base.hpp"

#include <cctype>

inline static u64 isd_xor_getu(const char *&p) {
  while (true) {
    u8 c = *p++;
    if (std::isdigit(c)) {
      u64 x = c ^ '0';
      for (c = *p++; std::isdigit(c); c = *p++)
        x = x * 10 + (c ^ '0');
      return x;
    }
  }
}

#ifndef ALGO_VERIFY

#include "../bench-1.hpp"

extern "C" u64 bm_isd_xor_getu(const char *p) {
  return _bm<isd_xor_getu>(p);
}

#else

#include "../strict-test-1.hpp"

int main() {
  _test_strict_getu<isd_xor_getu>();
}

#endif
