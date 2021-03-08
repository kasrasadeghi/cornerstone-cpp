// cornerstone includes
#include "parser.hpp"
#include "matcher.hpp"
#include "print.hpp"
#include "io.hpp"
#include "config.hpp"

// backbone includes
#include "backbone.hpp"

// tooling includes
#include "select.hpp"
#include "bbfmt.hpp"   // print_toplevel

int main(int argc, char* argv[])
  {
    if (argc != 4)
      {
        // CONSIDER: reading from stdin
        // CONSIDER putting argv[0] as the exec name
        println("USAGE: plumber <file> <pass> <selection>");
        println("       pass must be in {", backbone.get_passlist(), "}");
        return 0;
      }

    // parse arguments
    std::string filename = argv[1];
    std::string passname = argv[2];
    std::string selector_str = argv[3];

    if (not backbone.is_pass(passname))
      {
        println("ERROR: pass '", passname, "' not found!");
        println("USAGE: plumber <file> <pass> <selection>");
        println("       pass must be in {", backbone.get_passlist(), "}");
        return 1;
      }

    const Texp selector = Parser::parseTexp(selector_str);
    const Texp program = parse_from_file(filename);
    Texp curr = run_passes_until(program, passname);

    // print file
    println("; CMD: plumber ", argv[1], " ", argv[2], " '", argv[3], "'");
    println("; FILENAME: \"", program.value, "\"");

    // print after passrunner?
    // for (const auto& toplevel : curr)
    //   {
    //     println(toplevel.paren());
    //     return 0;
    //   }

    select(curr, selector, [](const Texp& match){ print_toplevel(match); });
  }
