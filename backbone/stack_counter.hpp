#pragma once

#include "grammar.hpp"
#include "matcher.hpp"
#include "io.hpp"
#include "config.hpp"

struct StackCounter {
  size_t _count = 0;
  size_t _sum = 0;
  Grammar& bb_tall_g;
  Matcher& bb_tall_m;

  StackCounter(Grammar& g, Matcher& m): bb_tall_g(g), bb_tall_m(m) {}

  void Let(const Texp& let, const Texp& proof);
  void Stmt(const Texp& stmt, const Texp& proof);
  void Do(const Texp& texp, const Texp& proof);
  void Def(const Texp& def, const Texp& proof);
  Texp newLocal();
};
