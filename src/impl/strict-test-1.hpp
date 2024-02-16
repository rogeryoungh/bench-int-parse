#pragma once

#include "../base.hpp"

#include <cstdio>
#include <vector>
#include <string>

template <auto func>
void _test(std::string s, const std::vector<u64> &v) {
  s.append(256, ' ');
  auto *p = s.c_str();
  for (u32 i = 0; i != v.size(); ++i) {
    u64 x = func(p);
    // std::printf("x = %lu\n", x);
    if (x != v[i]) {
      std::printf("error at %u: expect `%lu`, read `%lu`\n", i, v[i], x);
    }
  }
  // std::printf("success pass `%s`\n", s.data());
}

template <auto func>
void _test_strict_getu() {
  _test<func>("1 ", {1});
  _test<func>("1 1234\n12345678901234567", {1, 1234, 12345678901234567});
  _test<func>("1 123\n999  12457: xx 546 ", {1, 123, 999, 12457, 546});
}
