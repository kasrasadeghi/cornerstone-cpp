#include "pass.hpp"
#include "print.hpp"

#include "includer.hpp"
#include "normalize.hpp"
#include "type_expand.hpp"
#include "str.hpp"
#include "stack_counter.hpp"

/// region public pass runner ///===-------------------------------------===///

Texp passes(const Texp& tree) 
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

/// endregion public pass runner ///===----------------------------------===///
