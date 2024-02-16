#include "../../base.hpp"

#include <bit>

inline static u64 _swar_64(u64 u) {
  u = (u & 0x0f0f0f0f0f0f0f0f) * 0x0a01 >> 0x08;
  u = (u & 0x00ff00ff00ff00ff) * 0x00640001 >> 0x10;
  u = (u & 0x0000ffff0000ffff) * 0x271000000001 >> 0x20;
  return u;
}

inline static u64 swar_64_getu(const char *&p) {
  u64 x = 0;
  while (u8(*p - '0') > 9)
    p++;
  constexpr u32 p10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
  constexpr u64 cx30 = 0x3030303030303030;
  while (true) {
    u64 u = *reinterpret_cast<const u64 *>(p);
    u64 umask = u & (u + 0x0606060606060606) & 0xf0f0f0f0f0f0f0f0;
    if (umask == cx30) {
      p += 8;
      x = x * p10[8] + _swar_64(u);
    } else {
      u64 len = std::countr_zero(umask ^ cx30) >> 3;
      if (len != 0) {
        u <<= 64 - (len << 3);
        p += len;
        x = x * p10[len] + _swar_64(u);
      }
      break;
    }
  }
  p++;
  return x;
}

#ifndef ALGO_VERIFY

#include "../bench-1.hpp"

extern "C" u64 bm_swar_64_getu(const char *p) {
  return _bm<swar_64_getu>(p);
}

#else

#include "../strict-test-1.hpp"

int main() {
  _test_strict_getu<swar_64_getu>();
}

#endif
