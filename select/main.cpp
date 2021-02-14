#include "texp.hpp"
#include "parser.hpp"
#include "print.hpp"
#include "io.hpp"

#include "select.hpp"

int main(int argc, char* argv[])
  {
    if (argc != 3) {
      // CONSIDER: reading from stdin as
      // CONSIDER putting argv[0] as the exec name
      println("USAGE: select <file> <query> where the query is a subtexp query");
      return 0;
    }

    // parse arguments
    std::string filename = argv[1];
    std::string query_str = argv[2];

    const Texp query = Parser::parseTexp(query_str);

    // read program
    const Texp program = parse_from_file(filename);

    // TODO check that the query isn't more than one level deep

    println("; CMD: select ", argv[1], " \"", argv[2], "\"");

    select(program, query, [](const Texp& match){ println(match.paren()); });
  }
