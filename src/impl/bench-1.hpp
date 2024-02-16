#pragma once

#include "../base.hpp"

#define ALGO_REPEATx01(X) X
#define ALGO_REPEATx02(X) ALGO_REPEATx01(X), ALGO_REPEATx01(X)
#define ALGO_REPEATx04(X) ALGO_REPEATx02(X), ALGO_REPEATx02(X)
#define ALGO_REPEATx08(X) ALGO_REPEATx04(X), ALGO_REPEATx04(X)
#define ALGO_REPEATx16(X) ALGO_REPEATx08(X), ALGO_REPEATx08(X)
#define ALGO_REPEATx32(X) ALGO_REPEATx16(X), ALGO_REPEATx16(X)
#define ALGO_REPEATx64(X) ALGO_REPEATx64(X), ALGO_REPEATx64(X)

template <auto func, u32 n>
inline static u64 _bm_unroll(const char *p, u32 m) {
  u64 tmp = 0;
#ifdef __clang__
#pragma nounroll
#else
#pragma GCC nounroll
#endif
  for (u32 i = 0; i != m; ++i) {
    if constexpr (n == 1) {
      ALGO_REPEATx01(tmp |= func(p));
    } else if constexpr (n == 2) {
      ALGO_REPEATx02(tmp |= func(p));
    } else if constexpr (n == 4) {
      ALGO_REPEATx04(tmp |= func(p));
    } else if constexpr (n == 8) {
      ALGO_REPEATx08(tmp |= func(p));
    } else if constexpr (n == 16) {
      ALGO_REPEATx16(tmp |= func(p));
    } else if constexpr (n == 32) {
      ALGO_REPEATx32(tmp |= func(p));
    } else if constexpr (n == 64) {
      ALGO_REPEATx64(tmp |= func(p));
    } else {
      static_assert(n <= 64, "1 <= n <= 64\n");
    }
  }
  return tmp;
}

template <auto func>
inline static u64 _bm(const char *p) {
  constexpr u32 N = 1 << 20, U = 1;
  return _bm_unroll<func, U>(p, N / U);
}
