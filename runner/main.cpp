#include "parser.hpp"
#include "backbone.hpp"
#include "gen.hpp"
#include "matcher.hpp"
#include "print.hpp"
#include "io.hpp"
#include "config.hpp"

#include "includer.hpp"
#include "normalize.hpp"
#include "type_expand.hpp"
#include "str.hpp"
#include "stack_counter.hpp"

int main(int argc, char* argv[])
  {
    if (argc != 4)
      {
        // consider reading from stdin runner <pass>
        print("USAGE: runner <file> [--single|--until] <pass> for a pass in {", backbone.get_passlist(), "}\n");
        return 0;
      }

    // parse arguments
    std::string filename = argv[1];
    std::string option = argv[2];
    std::string passname = argv[3];

    if (option != "--single" && option != "--until")
      {
        println("ERROR: option '", option, "' is neither '--single' nor '--until'");
        print("USAGE: runner <file> [--single|--until] <pass> for a pass in {", backbone.get_passlist(), "}\n");
      }

    if (not backbone.is_pass(passname))
      {
        println("ERROR: pass '", passname, "' not found!");
        print("USAGE: runner <file> [--single|--until] <pass> for a pass in {", backbone.get_passlist(), "}\n");
        return 1;
      }

    // read program
    const Texp program = parse_from_file(filename);

    Texp result {""};
    if (option == "--single")
      {
        result = backbone.run_single_pass(program, passname);
      }
    else
      {
        // NOTE: until includes the named pass
        // assert(option == "--until");
        result = backbone.run_passes_until(program, passname);
      }

    for (const auto& toplevel : result)
      {
        println(toplevel.paren());
      }


    // TODO prove output
    // Grammar bb_g (parse_from_file(std::string(GRAMMAR_DIR) + "bb.texp")[0]);
    // Matcher bb_m {bb_g};

    // if (auto proof = bb_m.is(program, "Program"); proof.value == "success")
    //   {
    //     generate(bb_g, program, proof[0]);
    //     std::cout << "; " << proof[0] << std::endl;
    //   }
    // else
    //   {
    //     print(proof.tabs(), '\n');
    //     // print(program, '\n');
    //     std::cout << "grammar error with file: '" << (argc == 1 ? "STDIN" : argv[1]) << "'" << std::endl;
    //     exit(1);
    //   }
  }
