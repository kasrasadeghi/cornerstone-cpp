#include "parser.hpp"
#include "backbone_typeinfo.hpp"
#include "gen.hpp"
#include "matcher.hpp"
#include "print.hpp"
#include "io.hpp"
#include "config.hpp"

int main(int argc, char* argv[])
  {
    Texp program = (argc == 1) ? parse() : parse_from_file(argv[1]);

    program = backbone_typeinfo.run_all_passes(program);

    for (auto& child : program)
      {
        print(child, '\n');
      }
  }
