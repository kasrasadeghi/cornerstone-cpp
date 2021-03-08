#include "cond.hpp"
#include "matcher.hpp"

void UnionMatch(const Grammar& g,
                std::string_view parent_type_name,
                const Texp& texp,
                const Texp& proof,
                std::vector<std::pair<std::string_view, std::function<void(const Texp&, const Texp&)>>> cases,
                bool exhaustive)
  {
    CHECK(g.parseType(parent_type_name), "parent choice '" + std::string(parent_type_name) + "' not in grammar")
    Grammar::Type texp_type = parseChoice(g, proof, parent_type_name);
    for (auto pair : cases)
      {
        auto case_name = pair.first;
        auto case_f = pair.second;
        Grammar::Type case_type = CHECK_UNWRAP(g.parseType(case_name), "case '" + std::string(case_name) + "' not in grammar.");
        if (case_type == texp_type)
          {
            case_f(texp, proof);
            return;
          }
      }
    CHECK(not exhaustive, texp_type->name + " is unhandled in " + std::string(parent_type_name) + "()'s type switch");
  }
