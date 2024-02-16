#include "../../base.hpp"

#include <cstring>

template <class T>
T *_prepare_16_table() {
  constexpr u32 N = 0x10000;
  T *f = new T[N];
  std::memset(f, -1, N);
  for (u32 i = 0; i != 0x100; ++i) {
    for (u32 j = 0; j != 10; ++j) {
      u32 t = i * 0x100 | j | 0x30;
      if ('0' <= i && i <= '9')
        f[t] = j * 10 + i - 0x30;
      else
        f[t] = j | 0x100;
    }
  }
  return f;
}

inline u64 pre_16_getu(const char *&p) {
  static const auto *pre16 = _prepare_16_table<u16>();
  u8 c = *p++ - '0';
  while (c > 9)
    c = *p++ - '0';
  u64 x = c;
  while (true) {
    u16 t = *reinterpret_cast<const u16 *>(p);
    auto ft = pre16[t];
    p += 2;
    if (ft < 100) { // len = 2
      x = x * 100 + ft;
    } else { // len = 1
      if (ft < 0x1000)
        x = x * 10 + ft - 0x100;
      else
        --p;
      break;
    }
  }
  return x;
}

#ifndef ALGO_VERIFY

#include "../bench-1.hpp"

extern "C" u64 bm_pre_16_getu(const char *p) {
  return _bm<pre_16_getu>(p);
}

#else

#include "../strict-test-1.hpp"

int main() {
  _test_strict_getu<pre_16_getu>();
}

#endif
