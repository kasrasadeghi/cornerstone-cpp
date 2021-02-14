#include "parser.hpp"
#include "pass.hpp"
#include "gen.hpp"
#include "matcher.hpp"
#include "print.hpp"
#include "io.hpp"
#include "config.hpp"

int main(int argc, char* argv[])
  {
    if (argc != 2)
      {
        // CONSIDER: reading from stdin
        // CONSIDER putting argv[0] as the exec name
        println("USAGE: plumber <file> <pass> <selection>");
        println("       pass must be in {", get_passlist(), "}");
        return 0;
      }

    // parse arguments
    std::string filename = argv[1];
    std::string passname = argv[2];
    std::string selector_str = argv[3];

    if (not is_pass(passname))
      {
        println("ERROR: pass '", passname, "' not found!");
        println("USAGE: plumber <file> <pass> <selection>");
        println("       pass must be in {", get_passlist(), "}");
        return 1;
      }

    const Texp selector = Parser::parseTexp(selector_str);

    // read program
    const Texp program = parse_from_file(filename);

    // println(program.tabs());

    // print file
    println("; CMD: bbfmt ", argv[1]);
    println("; FILENAME: \"", program.value, "\"");


  }
