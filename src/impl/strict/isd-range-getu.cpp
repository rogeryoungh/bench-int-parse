#include "../../base.hpp"

inline static u64 isd_range_getu(const char *&p) {
  while (true) {
    u8 c = *p++;
    if ('0' <= c && c <= '9') {
      u64 x = c - '0';
      for (c = *p++; '0' <= c && c <= '9'; c = *p++)
        x = x * 10 + c - '0';
      return x;
    }
  }
}

#ifndef ALGO_VERIFY

#include "../bench-1.hpp"

extern "C" u64 bm_isd_range_getu(const char *p) {
  return _bm<isd_range_getu>(p);
}

#else

#include "../strict-test-1.hpp"

int main() {
  _test_strict_getu<isd_range_getu>();
}

#endif
