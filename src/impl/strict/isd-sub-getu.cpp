#include "../../base.hpp"

inline static u64 isd_sub_getu(const char *&p) {
  while (true) {
    u8 c = *p++ - '0';
    if (c <= 9) {
      u64 x = c;
      for (c = *p++ - '0'; c <= 9; c = *p++ - '0')
        x = x * 10 + c;
      return x;
    }
  }
}

#ifndef ALGO_VERIFY

#include "../bench-1.hpp"

extern "C" u64 bm_isd_sub_getu(const char *p) {
  return _bm<isd_sub_getu>(p);
}

#else

#include "../strict-test-1.hpp"

int main() {
  _test_strict_getu<isd_sub_getu>();
}

#endif
