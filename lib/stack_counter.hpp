#pragma once

#include "texp.hpp"
#include "grammar.hpp"
#include "matcher.hpp"
#include "io.hpp"

struct StackCounter {
  size_t _count = 0;
  size_t _sum = 0;
  Grammar bb_tall_g {parse_from_file("docs/bb-type-tall-grammar.texp")[0]};
  Matcher bb_tall_m {bb_tall_g};

  void Let(const Texp& let, const Texp& proof);
  void Stmt(const Texp& stmt, const Texp& proof);
  void Do(const Texp& texp, const Texp& proof);
  StackCounter(const Texp& def, const Texp& proof);
  Texp newLocal();
};
