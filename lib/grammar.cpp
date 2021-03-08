#include "grammar.hpp"
#include "macros.hpp"
#include "matcher.hpp"

auto operator<< (std::ostream& o, Grammar::Type t) -> std::ostream&
  { return o << t->name; }

Grammar::Grammar(Texp t)
  {
    CHECK(t.value == "Grammar", "value at root of given texp is not 'Grammar'");
    for (auto& child : t)
      {
        CHECK(0 != child.size(), "a production of a grammar should not be empty");
        types.emplace_back(child.value, child[0]);
      }
  }

std::optional<Grammar::Type> Grammar::parseType(std::string_view s) const
  {
    auto iter = std::find_if(types.cbegin(), types.cend(), [s](const TypeRecord& tr) { return tr.name == s; });
    if (iter != types.cend())
      return iter;
    else
      return std::nullopt;
  }

Grammar::Type Grammar::shouldParseType(std::string_view s) const
  {
    auto iter = std::find_if(types.cbegin(), types.cend(), [s](const TypeRecord& tr) { return tr.name == s; });
    CHECK(iter != types.cend(), std::string(s) + " not in grammar");
    return iter;
  }

const Texp& Grammar::getProduction(Type type) const
  { return type->production; }

std::optional<std::string_view> Grammar::getKeyword(std::string_view s) const
  {
    Type type = shouldParseType(s);
    if (type->production.value.starts_with("#") || type->production.value == "|")
      return std::nullopt;
    else
      return type->production.value;
  }
