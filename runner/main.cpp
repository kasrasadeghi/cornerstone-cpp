#include "parser.hpp"
#include "pass.hpp"
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
    // TODO using backbone::pass_list;
    const std::vector<std::pair<std::string_view, std::function<void(Texp&)>>>& passes =
      {
        {"include",   [](Texp& t) { Includer  p; t = p.Program(t); }},
        {"str",       [](Texp& t) { Str       p; t = p.Program(t); }},
        {"normalize", [](Texp& t) { Normalize p; t = p.Program(t); }},
        {"typeinfer", [](Texp& t) { TypeInfer p; t = p.Program(t); }},
      };

    if (argc != 3)
      {
        // consider reading from stdin runner <pass>
        print("USAGE: runner <file> <pass> for a pass in {", get_passlist(), "}");
        return 0;
      }

    // parse arguments
    std::string filename = argv[1];
    std::string passname = argv[2];

    if (not is_pass(passname))
      {
        println("ERROR: pass '", passname, "' not found!");
        print("USAGE: runner <file> <pass> for a pass in {", get_passlist(), "}");
        return 1;
      }

    // read program
    const Texp program = parse_from_file(filename);
    Texp curr = program; // mutable copy

    for (const auto& [curr_passname, passf] : passes)
      {
        passf(curr);
        if (curr_passname == passname)
          {
            // don't print the filename, print the toplevels
            for (const auto& toplevel : curr)
              {
                println(toplevel.paren());
              }
            return 0;
          }
      }

    // TODO prove output
    // Grammar bb_g (parse_from_file(std::string(GRAMMAR_DIR) + "bb-grammar.texp")[0]);
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
