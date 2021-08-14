#include "pass_config.hpp"
#include "macros.hpp"

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

Texp PassConfig::run_passes_until(Texp curr, std::string_view passname)
  {
    for (const auto& [curr_passname, passf] : pass_table)
      {
        passf(curr); // passed by reference
        if (curr_passname == passname)
          {
            return curr;
          }
      }

    auto str = [](auto s) { return std::string(s); };

    CHECK(false, str("passname '") + str(passname) + str("' not in ") + get_passlist());
  }

Texp PassConfig::run_single_pass(Texp curr, std::string_view passname)
  {
    for (const auto& [curr_passname, passf] : pass_table)
      {
        if (curr_passname == passname)
          {
            passf(curr); // passed by reference
            return curr;
          }
      }

    auto str = [](auto s) { return std::string(s); };

    CHECK(false, str("passname '") + str(passname) + str("' not in ") + get_passlist());
  }
