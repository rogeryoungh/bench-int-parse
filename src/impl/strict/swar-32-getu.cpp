#include "../../base.hpp"

#include <bit>

inline static u32 _swar_32(u32 u) {
  u = (u & 0x0f0f0f0f) * 0x0a01 >> 0x08;
  u = (u & 0x00ff00ff) * 0x00640001 >> 0x10;
  return u;
}

inline static u64 swar_32_getu(const char *&p) {
  u64 x = 0;
  while (u8(*p - '0') > 9)
    p++;
  constexpr u32 p10[] = {1, 10, 100, 1000, 10000};
  constexpr u32 cx30 = 0x30303030;
  while (true) {
    u32 u = *reinterpret_cast<const u32 *>(p);
    u32 umask = u & (u + 0x06060606) & 0xf0f0f0f0;
    if (umask == cx30) { // len = 4
      p += 4;
      x = x * p10[4] + _swar_32(u);
    } else {
      u32 len = std::countr_zero<u32>(umask ^ cx30) >> 3;
      if (len != 0) {
        u <<= 32 - (len << 3);
        p += len;
        x = x * p10[len] + _swar_32(u);
      }
      break;
    }
  }
  p++;
  return x;
}

#ifndef ALGO_VERIFY

#include "../bench-1.hpp"

extern "C" u64 bm_swar_32_getu(const char *p) {
  return _bm<swar_32_getu>(p);
}

#else

#include "../strict-test-1.hpp"

int main() {
  _test_strict_getu<swar_32_getu>();
}

#endif
