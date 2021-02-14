#include "texp.hpp"
#include <functional>

constexpr static std::string_view PLACEHOLDER = "_";

void select(const Texp& program, const Texp& query, std::function<void(const Texp&)> consumer, std::string_view placeholder = PLACEHOLDER)
  {
    // do one level of literal match
    for (const auto& child : program) {

      // the child matches if it has the same value as the query, and the same one-level pattern for the children's literals
      if (child.value == query.value) {

        if (query.size() > child.size()) continue;

        bool failure = false;

        // match as long as the query is
        for (int i = 0; i < query.size(); ++i) {
          if (query[i].value == placeholder) continue;

          if (child[i].value != query[i].value)
            {
              failure = true;
              break;
            }
        }

        if (not failure)
          {
            consumer(child);
          }
      }
    }
  }
