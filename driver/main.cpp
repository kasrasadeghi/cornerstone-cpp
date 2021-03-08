#include "parser.hpp"
#include "backbone.hpp"
#include "gen.hpp"
#include "matcher.hpp"
#include "print.hpp"
#include "io.hpp"
#include "config.hpp"

int main(int argc, char* argv[])
  {
    Texp program = (argc == 1) ? parse() : parse_from_file(argv[1]);

    program = backbone.run_all_passes(program);

    Grammar bb_g (parse_from_file(std::string(GRAMMAR_DIR) + "bb-grammar.texp")[0]);
    Matcher bb_m {bb_g};

    if (auto proof = bb_m.is(program, "Program"); proof.value == "success")
      {
        generate(bb_g, program, proof[0]);
        std::cout << "; " << proof[0] << std::endl;
      }
    else
      {
        print(proof.tabs(), '\n');
        // print(program, '\n');
        std::cout << "grammar error with file: '" << (argc == 1 ? "STDIN" : argv[1]) << "'" << std::endl;
        exit(1);
      }
  }
