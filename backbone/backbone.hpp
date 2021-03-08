#pragma once
#include "texp.hpp"
#include "pass_config.hpp"

extern PassConfig backbone;



Texp run_passes_until(Texp input, std::string_view s);
