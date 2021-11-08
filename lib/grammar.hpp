#pragma once
#include "parser.hpp"
#include "macros.hpp"
#include <string_view>
#include <optional>
#include <functional>

class Grammar {
public:
  class TypeRecord {
  public:
  std::string name;
  Texp production;
  TypeRecord(std::string n, Texp p): name(n), production(p) {}
};

std::vector<TypeRecord> types;

using Type = std::vector<TypeRecord>::const_iterator;

Grammar(Texp t);
std::optional<Type> parseType(std::string_view s) const;
Type shouldParseType(std::string_view s) const;
const Texp& getProduction(Type type) const;
std::optional<std::string_view> getKeyword(std::string_view s) const;
};
