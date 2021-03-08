#include "pass.hpp"
#include "print.hpp"

#include "includer.hpp"
#include "normalize.hpp"
#include "type_expand.hpp"
#include "str.hpp"
#include "stack_counter.hpp"

/// region pass ///===-------------------------------------===///

const std::vector<std::pair<std::string_view, std::function<void(Texp&)>>> backbone::pass_config =
  {
    {"include",   [](Texp& t) {
      Grammar g {parse_from_file(std::string(GRAMMAR_DIR) + "bb-type-tall-str-include-grammar.texp")[0]};
      Matcher m {g};
      Texp proof = RESULT_UNWRAP(m.is(t, "Program"), "given texp is not a bb-type-tall-str-include Program:\n  " + t.paren());
      Includer i {g, m};
      t = i.Program(t, proof);
    }},
    {"str",       [](Texp& t) {
      constexpr std::string_view filename = "bb-type-tall-str-grammar.texp";

      Grammar g {parse_from_file(std::string(GRAMMAR_DIR) + std::string(filename))[0]};
      Matcher m {g};
      Texp proof = RESULT_UNWRAP(m.is(t, "Program"), "given texp is not a bb-type-tall-str Program:\n  " + t.paren());
      Str s {g, m};
      t = s.Program(t, proof);
    }},
    {"normalize", [](Texp& t) { Normalize p; t = p.Program(t); }},
    {"typeinfer", [](Texp& t) { TypeInfer p; t = p.Program(t); }},
  };

Texp run_all_passes(const Texp& tree)
  {
    Texp curr = tree;

    (backbone::pass_config[0].second)(curr);
    (backbone::pass_config[1].second)(curr);
    {
      Normalize n;
      curr = n.Program(curr);
    }
    {
      TypeInfer t;
      curr = t.Program(curr);
    }
    return curr;
  }

std::string get_passlist(void)
  {
    std::string acc;
    for (const auto& pass : backbone::pass_config)
      {
        if (&pass != &backbone::pass_config[0]) { acc += ", "; }
        acc += pass.first;
      }
    return acc;
  }

bool is_pass(std::string_view passname)
  {
    for (const auto& [curr_passname, passf]: backbone::pass_config)
      {
        if (passname == curr_passname)
          {
            return true;
          }
      }

    return false;
  }

Texp run_passes_until(Texp curr, std::string_view passname)
  {
    for (const auto& [curr_passname, passf] : backbone::pass_config)
      {
        passf(curr);
        if (curr_passname == passname)
          {
            return curr;
          }
      }

    auto str = [](auto s) { return std::string(s); };

    CHECK(false, str("passname '") + str(passname) + str("' not in ") + get_passlist());
  }

/// endregion pass ///===----------------------------------===///
