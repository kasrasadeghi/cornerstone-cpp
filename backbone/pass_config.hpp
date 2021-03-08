#pragma once
#include "texp.hpp"

#include <functional>

struct PassConfig {
  const std::vector<std::pair<std::string_view, std::function<void(Texp&)>>> pass_table;

  Texp run_all_passes(const Texp& tree);

  std::string get_passlist(void);

  bool is_pass(std::string_view passname);

  Texp run_passes_until(Texp input, std::string_view passname);
};
