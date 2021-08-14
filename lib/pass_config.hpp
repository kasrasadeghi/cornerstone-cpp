#pragma once
#include "texp.hpp"

#include <functional>

// CONSIDER: the pass config should also have the generator in it
// - a generator has an input grammar and a function that actually generates some output
struct PassConfig {
  const std::vector<std::pair<std::string_view, std::function<void(Texp&)>>> pass_table;

  Texp run_all_passes(const Texp& tree);

  std::string get_passlist(void);

  bool is_pass(std::string_view passname);

  Texp run_passes_until(Texp input, std::string_view passname);

  Texp run_single_pass(Texp input, std::string_view passname);
};
