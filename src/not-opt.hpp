#pragma once

#if defined(_MSC_VER)
void doNotOptimizeAwaySink(void const *);

template <typename T>
void doNotOptimizeAway(T const &val);

#else

// These assembly magic is directly from what Google Benchmark is doing. I have previously used what
// facebook's folly was doing, but this seemed to have compilation problems in some cases. Google
// Benchmark seemed to be the most well tested anyways. see
// https://github.com/google/benchmark/blob/v1.7.1/include/benchmark/benchmark.h#L443-L446
template <typename T>
void doNotOptimizeAway(T const &val) {
  // NOLINTNEXTLINE(hicpp-no-assembler)
  asm volatile("" : : "r,m"(val) : "memory");
}

template <typename T>
void doNotOptimizeAway(T &val) {
#if defined(__clang__)
  // NOLINTNEXTLINE(hicpp-no-assembler)
  asm volatile("" : "+r,m"(val) : : "memory");
#else
  // NOLINTNEXTLINE(hicpp-no-assembler)
  asm volatile("" : "+m,r"(val) : : "memory");
#endif
}
#endif
