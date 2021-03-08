#pragma once
#include "texp.hpp"

#include <functional>

struct PassConfig {
  const std::vector<std::pair<std::string_view, std::function<void(Texp&)>>> pass_table;
};
