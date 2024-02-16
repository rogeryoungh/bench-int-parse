#include "../../base.hpp"

inline static u64 isd_goto_getu(const char *&p) {
  u32 c;
  u64 x;
algo_l1:
  c = p[0];
  ++p;
  c -= '0';
  if (c > 9)
    goto algo_l1;
  x = c;
algo_l2:
  c = p[0];
  ++p;
  c -= '0';
  if (c > 9)
    return x;
  x = x * 10 + c;
  goto algo_l2;
}

#ifndef ALGO_VERIFY

#include "../bench-1.hpp"

extern "C" u64 bm_isd_goto_getu(const char *p) {
  return _bm<isd_goto_getu>(p);
}

#else

#include "../strict-test-1.hpp"

int main() {
  _test_strict_getu<isd_goto_getu>();
}

#endif
