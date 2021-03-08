#include "backbone.hpp"
#include "print.hpp"

#include "includer.hpp"
#include "normalize.hpp"
#include "type_expand.hpp"
#include "str.hpp"
#include "stack_counter.hpp"

/// region pass ///===-------------------------------------===///

PassConfig backbone {
  .pass_table = {
    {"include",   [](Texp& t) {
      constexpr std::string_view filename = "bb-type-tall-str-include-grammar.texp";

      Grammar g {parse_from_file(std::string(GRAMMAR_DIR) + std::string(filename))[0]};
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
    {"normalize", [](Texp& t) {
      constexpr std::string_view filename = "bb-type-tall-grammar.texp";

      Grammar g {parse_from_file(std::string(GRAMMAR_DIR) + std::string(filename))[0]};
      Matcher m {g};
      Texp proof = RESULT_UNWRAP(m.is(t, "Program"), "given texp is not a bb-type-tall Program:\n  " + t.paren());
      Normalize p {g, m};
      t = p.Program(t, proof);
    }},
    {"typeinfer", [](Texp& t) {
      constexpr std::string_view filename = "bb-type-grammar.texp";

      Grammar g {parse_from_file(std::string(GRAMMAR_DIR) + std::string(filename))[0]};
      Matcher m {g};
      Texp proof = RESULT_UNWRAP(m.is(t, "Program"), "given texp is not a bb-type Program:\n  " + t.paren());
      TypeInfer p {g, m};
      t = p.Program(t, proof);
    }},
  }
};

bool is_pass(std::string_view passname)
  {
    for (const auto& [curr_passname, passf]: backbone.pass_table)
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
    for (const auto& [curr_passname, passf] : backbone.pass_table)
      {
        passf(curr);
        if (curr_passname == passname)
          {
            return curr;
          }
      }

    auto str = [](auto s) { return std::string(s); };

    CHECK(false, str("passname '") + str(passname) + str("' not in ") + backbone.get_passlist());
  }

/// endregion pass ///===----------------------------------===///
