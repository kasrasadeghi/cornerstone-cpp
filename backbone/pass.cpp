#include "pass.hpp"
#include "print.hpp"

#include "includer.hpp"
#include "normalize.hpp"
#include "type_expand.hpp"
#include "str.hpp"
#include "stack_counter.hpp"

/// region pass ///===-------------------------------------===///

static const std::vector<std::pair<std::string_view, std::function<void(Texp&)>>> PASSES =
  {
    {"include",   [](Texp& t) { Includer  p; t = p.Program(t); }},
    {"str",       [](Texp& t) { Str       p; t = p.Program(t); }},
    {"normalize", [](Texp& t) { Normalize p; t = p.Program(t); }},
    {"typeinfer", [](Texp& t) { TypeInfer p; t = p.Program(t); }},
  };

Texp run_all_passes(const Texp& tree)
  {
    Texp curr = tree;
    {
      Includer i;
      curr = i.Program(curr);
    }
    {
      Str s;
      curr = s.Program(curr);
    }
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
    for (const auto& pass : PASSES)
      {
        if (&pass != &PASSES[0]) { acc += ", "; }
        acc += pass.first;
      }
    return acc;
  }

bool is_pass(std::string_view passname)
  {
    for (const auto& [curr_passname, passf]: PASSES)
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
    for (const auto& [curr_passname, passf] : PASSES)
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
