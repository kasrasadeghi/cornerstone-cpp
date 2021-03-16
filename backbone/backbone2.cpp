#include "backbone2.hpp"
#include "print.hpp"

#include "includer.hpp"
#include "normalize.hpp"
#include "type_expand.hpp"
#include "str.hpp"
#include "stack_counter.hpp"

PassConfig backbone2 {
  .pass_table = {
    {"include",   [](Texp& t) {
      constexpr std::string_view filename = "bb2-type-tall-str-include.texp";

      Grammar g {parse_from_file(std::string(GRAMMAR_DIR) + std::string(filename))[0]};
      Matcher m {g};
      Texp proof = RESULT_UNWRAP(m.is(t, "Program"), "given texp is not a bb2-type-tall-str-include Program:\n  " + t.paren());
      Includer i {g, m};
      t = i.Program(t, proof);
    }},
    {"str",       [](Texp& t) {
      constexpr std::string_view filename = "bb2-type-tall-str.texp";

      Grammar g {parse_from_file(std::string(GRAMMAR_DIR) + std::string(filename))[0]};
      Matcher m {g};
      Texp proof = RESULT_UNWRAP(m.is(t, "Program"), "given texp is not a bb2-type-tall-str Program:\n  " + t.paren());
      Str s {g, m};
      t = s.Program(t, proof);
    }},
    {"normalize", [](Texp& t) {
      constexpr std::string_view filename = "bb2-type-tall.texp";

      Grammar g {parse_from_file(std::string(GRAMMAR_DIR) + std::string(filename))[0]};
      Matcher m {g};
      Texp proof = RESULT_UNWRAP(m.is(t, "Program"), "given texp is not a bb2-type-tall Program:\n  " + t.paren());
      Normalize p {g, m};
      t = p.Program(t, proof);
    }},
    {"typeinfer", [](Texp& t) {
      constexpr std::string_view filename = "bb2-type.texp";

      Grammar g {parse_from_file(std::string(GRAMMAR_DIR) + std::string(filename))[0]};
      Matcher m {g};
      Texp proof = RESULT_UNWRAP(m.is(t, "Program"), "given texp is not a bb2-type Program:\n  " + t.paren());
      TypeInfer p {g, m};
      t = p.Program(t, proof);
    }},
  }
};
