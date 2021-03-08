#include "parser.hpp"
#include "backbone.hpp"
#include "gen.hpp"
#include "matcher.hpp"
#include "print.hpp"
#include "io.hpp"
#include "config.hpp"

#include "bbfmt.hpp"

int main(int argc, char* argv[])
  {
    if (argc != 2) {
      // CONSIDER: reading from stdin
      // CONSIDER putting argv[0] as the exec name
      println("USAGE: bbfmt <file>");
      return 0;
    }

    // parse arguments
    std::string filename = argv[1];

    // read program
    const Texp program = parse_from_file(filename);

    // println(program.tabs());

    // print file
    println("; CMD: bbfmt ", argv[1]);
    println("; FILENAME: \"", program.value, "\"");

    print_program(program);
  }
