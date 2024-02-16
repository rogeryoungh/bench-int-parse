#include "../../base.hpp"

#include <bit>

inline static u16 _swar_16(u16 u) {
  u = u16((u & 0x0f0f) * 0x0a01) >> 0x08;
  return u;
}

inline static u64 swar_16_getu(const char *&p) {
  u64 x = 0;
  while (u8(*p - '0') > 9)
    ++p;
  constexpr u32 p10[] = {1, 10, 100};
  while (true) {
    u16 u = *reinterpret_cast<const u16 *>(p);
    u16 umask = u & (u + 0x0606) & 0xf0f0;
    if (umask == 0x3030) { // len = 2
      x = x * p10[2] + _swar_16(u);
      p += 2;
    } else {
      u32 len = std::countr_zero<u16>(umask ^ 0x3030) >> 3;
      if (len != 0) {
        u <<= 16 - (len << 3);
        p += len;
        x = x * p10[len] + _swar_16(u);
      }
      break;
    }
  }
  p++;
  return x;
}

#ifndef ALGO_VERIFY

#include "../bench-1.hpp"

extern "C" u64 bm_swar_16_getu(const char *p) {
  return _bm<swar_16_getu>(p);
}

#else

#include "../strict-test-1.hpp"

int main() {
  _test_strict_getu<swar_16_getu>();
}

#endif
