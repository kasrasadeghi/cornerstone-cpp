#pragma once
#include "texp.hpp"
#include "grammar.hpp"
#include "matcher.hpp"
#include "pass.hpp"
#include "result.hpp"
#include "io.hpp"
#include "print.hpp"
#include "config.hpp"

/// include ///===--------------------------------------------------------===///

/// a naive includer, like #include in C but without declaration reconciliation.
/// - uses relative paths from the current file
struct Includer {
Grammar g;
Matcher m;
std::string _dirname;
std::string _basename;

Includer():
  g(parse_from_file(std::string(GRAMMAR_DIR) + "bb-type-tall-str-include-grammar.texp")[0]), m(g) {}

Texp Program(const Texp& texp)
  {
    Texp program_proof = RESULT_UNWRAP(m.is(texp, "Program"), "given texp is not a bb-type-tall-str-include Program:\n  " + texp.paren());
    Texp this_program {texp.value};

    auto basename =
      [](std::string path) -> std::string
        { return path.substr(path.rfind('/') + 1); };

    auto dirname =
      [](std::string path) -> std::string
        { return path.substr(0, path.rfind('/') + 1); };

    _basename = basename(texp.value);
    _dirname  = dirname (texp.value);

    for (int i = 0; i < texp.size(); ++i)
      for (auto child : TopLevel(texp[i], program_proof[i]))
        this_program.push(child);

    return this_program;
  }

Texp TopLevel(const Texp& texp, const Texp& proof)
  {
    Texp result {"*TopLevel"};
    if (parseChoice(g, proof, "TopLevel") == g.shouldParseType("Include"))
      for (auto child : Include(texp, proof))
        result.push(child);
    else
      result.push(texp);
    return result;
  }

Texp Include(const Texp& texp, const Texp& proof)
  {
    // logical note: substr arguments are index offset and length, not an interval.
    auto remove_quotes_from_str = [](const std::string& s) -> std::string
      { return s.substr(1, s.length() - 2); };

    auto filename = _dirname + remove_quotes_from_str(texp[0].value);

    // NOTE: this includer instance is to allow for a recursive stack
    // - needed for multiple relative-paths includes
    Includer includer;
    Texp result = includer.Program(parse_from_file(filename));
    result.value = "*TopLevel";
    return result;
  }
};
