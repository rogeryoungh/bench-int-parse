#include "../base.hpp"

#ifndef BM_CASE
#define BM_CASE 0
#endif

#if BM_CASE == 0
#define BM_FUNC bm_isd_0_getu
#define BM_NAME "isd-0      "
#elif BM_CASE == 1
#define BM_FUNC bm_isd_u8_getu
#define BM_NAME "isd-u8     "
#elif BM_CASE == 2
#define BM_FUNC bm_isd_sub_1_getu
#define BM_NAME "isd-sub-1  "
#elif BM_CASE == 3
#define BM_FUNC bm_isd_sub_2_getu
#define BM_NAME "isd-sub-2  "
#elif BM_CASE == 4
#define BM_FUNC bm_isd_range_1_getu
#define BM_NAME "isd-range-1  "
#elif BM_CASE == 5
#define BM_FUNC bm_swar_16_getu
#define BM_NAME "swar-16    "
#elif BM_CASE == 6
#define BM_FUNC bm_swar_16_1_getu
#define BM_NAME "swar-16-1  "
#elif BM_CASE == 7
#define BM_FUNC bm_swar_32_getu
#define BM_NAME "swar-32    "
#elif BM_CASE == 8
#define BM_FUNC bm_swar_64_getu
#define BM_NAME "swar-64    "
#elif BM_CASE == 9
#define BM_FUNC bm_pre_16_getu
#define BM_NAME "pre-16     "
#endif

extern "C" u64 BM_FUNC(const char *p);

#define ANKERL_NANOBENCH_IMPLEMENT
#include "../nanobench/nanobench.h"

constexpr u32 N = 1 << 20;

constexpr char patterns[] = "12345678901234567890";
alignas(0x1000) char *buf = new char[20 * N];

void prepare(u32 len) {
  char *p = buf;
  char tmp[32];
  std::copy_n(patterns, len, tmp);
  tmp[len] = ' ';
  for (u32 i = 0; i != N; ++i) {
    p = std::copy_n(tmp, len + 1, p);
  }
  std::fill_n(p, 256, ' ');
}

template <auto func>
void test(const char *name) {
  ankerl::nanobench::Bench bench;
  bench.title(name);
  bench.minEpochIterations(0x10);
  bench.warmup(2);
  // bench.performanceCounters(true);

  // for (u32 i : {16, 12, 8, 4, 1, 2, 1}) {
  for (u32 i = 18; i != 0; --i) {
    std::string si = std::string("len=") + std::to_string(i);
    prepare(i);
    // func(buf);
    // asm volatile("mfence" ::: "memory");
    bench.run(si, [] {
      // asm volatile("mfence" ::: "memory");
      ankerl::nanobench::doNotOptimizeAway(func(buf));
    });
  }
}

int main() {
  test<BM_FUNC>(BM_NAME);
}
