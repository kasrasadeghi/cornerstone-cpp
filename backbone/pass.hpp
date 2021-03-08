#pragma once
#include "texp.hpp"

#include <functional>

namespace backbone {
  extern const std::vector<std::pair<std::string_view, std::function<void(Texp&)>>> pass_config;
};

Texp run_all_passes(const Texp& tree);

std::string get_passlist(void);

bool is_pass(std::string_view s);

Texp run_passes_until(Texp input, std::string_view s);
