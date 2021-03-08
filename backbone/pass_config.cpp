#include "pass_config.hpp"

Texp PassConfig::run_all_passes(const Texp& tree)
  {
    Texp curr = tree;

    for (auto& [name, f] : pass_table) {
      f(curr);
    }

    return curr;
  }
