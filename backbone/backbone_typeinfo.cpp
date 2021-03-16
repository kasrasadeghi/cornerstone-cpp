#include "backbone_typeinfo.hpp"

#include "print.hpp"
#include "includer.hpp"
#include "normalize.hpp"
#include "typeinfo.hpp"
#include "str.hpp"
#include "stack_counter.hpp"

PassConfig backbone_typeinfo {
  .pass_table = {
    {"include",   [](Texp& t) {
      constexpr std::string_view filename = "bb-type-tall-str-include.texp";

      Grammar g {parse_from_file(std::string(GRAMMAR_DIR) + std::string(filename))[0]};
      Matcher m {g};
      Texp proof = RESULT_UNWRAP(m.is(t, "Program"), "given texp is not a bb-type-tall-str-include Program:\n  " + t.paren());
      Includer i {g, m};
      t = i.Program(t, proof);
    }},
    {"str",       [](Texp& t) {
      constexpr std::string_view filename = "bb-type-tall-str.texp";

      Grammar g {parse_from_file(std::string(GRAMMAR_DIR) + std::string(filename))[0]};
      Matcher m {g};
      Texp proof = RESULT_UNWRAP(m.is(t, "Program"), "given texp is not a bb-type-tall-str Program:\n  " + t.paren());
      Str s {g, m};
      t = s.Program(t, proof);
    }},
    {"normalize", [](Texp& t) {
      constexpr std::string_view filename = "bb-type-tall.texp";

      Grammar g {parse_from_file(std::string(GRAMMAR_DIR) + std::string(filename))[0]};
      Matcher m {g};
      Texp proof = RESULT_UNWRAP(m.is(t, "Program"), "given texp is not a bb-type-tall Program:\n  " + t.paren());
      Normalize p {g, m};
      t = p.Program(t, proof);
    }},
    {"typeinfo", [](Texp& t) {
      constexpr std::string_view filename = "bb-type.texp";

      Grammar g {parse_from_file(std::string(GRAMMAR_DIR) + std::string(filename))[0]};
      Matcher m {g};
      Texp proof = RESULT_UNWRAP(m.is(t, "Program"), "given texp is not a bb-type Program:\n  " + t.paren());
      TypeInfo p {g, m};
      /* discarded */ (void)p.Program(t, proof);
      t = p.env.result;
    }},
  }
};
