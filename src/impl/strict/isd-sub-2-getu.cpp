#include "../../base.hpp"

inline static u64 isd_sub_2_getu(const char *&p) {
#define NXT                                                                                        \
  c = *p++;                                                                                        \
  if ('0' <= c && c <= '9')                                                                        \
    x = x * 10 + c - '0';                                                                          \
  else                                                                                             \
    return x;
#define NXT3 NXT NXT NXT
  u64 x = 0;
  while (true) {
    u8 c = *p++ - '0';
    if (c <= 9) {
      x = c;
      NXT3 NXT3 NXT3 NXT3 NXT3 NXT3
    }
  }
#undef NXT
#undef NXT3
}

#ifndef ALGO_VERIFY

#include "../bench-1.hpp"

extern "C" u64 bm_isd_sub_2_getu(const char *p) {
  return _bm<isd_sub_2_getu>(p);
}

#else

#include "../strict-test-1.hpp"

int main() {
  _test_strict_getu<isd_sub_2_getu>();
}

#endif
