#include "pass.hpp"
#include "print.hpp"

#include "includer.hpp"
#include "normalize.hpp"
#include "type_expand.hpp"
#include "str.hpp"
#include "stack_counter.hpp"

/// region pass ///===-------------------------------------===///

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
    const std::vector<std::pair<std::string_view, std::function<void(Texp&)>>>& passes =
      {
        {"include",   [](Texp& t) { Includer  p; t = p.Program(t); }},
        {"str",       [](Texp& t) { Str       p; t = p.Program(t); }},
        {"normalize", [](Texp& t) { Normalize p; t = p.Program(t); }},
        {"typeinfer", [](Texp& t) { TypeInfer p; t = p.Program(t); }},
      };

    std::string acc;
    for (const auto& pass : passes)
      {
        if (&pass != &passes[0]) { acc += ", "; }
        acc += pass.first;
      }
    return acc;
  }

bool is_pass(std::string_view s)
  {
    for (const auto& [curr_passname, passf]: passes)
      {
        if (passname == curr_passname)
          {
            return true;
          }
      }

    return false;
  }

/// endregion pass ///===----------------------------------===///
