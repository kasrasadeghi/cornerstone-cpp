#pragma once
#include "texp.hpp"

Texp run_all_passes(const Texp& tree);

std::string get_passlist(void);

bool is_pass(std::string_view s);
