#include "../../base.hpp"

inline static u64 swar_16_1_getu(const char *&p) {
  u8 c = *p++ - '0';
  while (c > 9)
    c = *p++ - '0';
  u64 x = c;
  while (true) {
    u16 u = *reinterpret_cast<const u16 *>(p);
    u16 umask = u & (u + 0x0606) & 0xf0f0;
    if (umask == 0x3030) { // len == 2
      u = u16((u & 0x0f0fu) * 0x0a01) >> 0x08;
      p += 2;
      x = x * 100 + u;
    } else {
      if ((umask & 0xff) == 0x30) { // len == 1
        x = x * 10 + (u & 0xf);
        p += 2;
      } else {
        p += 1;
      }
      return x;
    }
  }
}

#ifndef ALGO_VERIFY

#include "../bench-1.hpp"

extern "C" u64 bm_swar_16_1_getu(const char *p) {
  return _bm<swar_16_1_getu>(p);
}

#else

#include "../strict-test-1.hpp"

int main() {
  _test_strict_getu<swar_16_1_getu>();
}

#endif
