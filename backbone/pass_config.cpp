#include "pass_config.hpp"

Texp PassConfig::run_all_passes(const Texp& tree)
  {
    Texp curr = tree;

    for (auto& [name, f] : pass_table) {
      f(curr);
    }

    return curr;
  }

std::string PassConfig::get_passlist(void)
  {
    std::string acc;
    for (const auto& pass : pass_table)
      {
        if (&pass != &pass_table[0]) { acc += ", "; }
        acc += pass.first;
      }
    return acc;
  }

bool PassConfig::is_pass(std::string_view passname)
  {
    for (const auto& [curr_passname, passf]: pass_table)
      {
        if (passname == curr_passname)
          {
            return true;
          }
      }

    return false;
  }
