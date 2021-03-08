#include "grammar.hpp"

void UnionMatch(const Grammar& g,
                std::string_view parent_type_name,
                const Texp& texp,
                const Texp& proof,
                std::vector<std::pair<std::string_view, std::function<void(const Texp&, const Texp&)>>> cases,
                bool exhaustive = true);
