#include "texp.hpp"
#include "parser.hpp"
#include "print.hpp"
#include "io.hpp"

constexpr static std::string_view PLACEHOLDER = "_";

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

    // do one level of literal match
    for (const auto& child : program) {

      // the child matches if it has the same value as the query, and the same one-level pattern for the children's literals
      if (child.value == query.value) {

        if (query.size() > child.size()) continue;

        bool failure = false;

        // match as long as the query is
        for (int i = 0; i < query.size(); ++i) {
          if (query[i].value == PLACEHOLDER) continue;

          if (child[i].value != query[i].value)
            {
              failure = true;
              break;
            }
        }

        if (not failure)
          {
            println(child.paren());
          }
      }
    }
  }
