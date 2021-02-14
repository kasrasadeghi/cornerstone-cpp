#include "parser.hpp"
#include "pass.hpp"
#include "gen.hpp"
#include "matcher.hpp"
#include "print.hpp"
#include "io.hpp"
#include "config.hpp"

// TODO: don't delete comments and between statement spacing?

void print_do(const Texp& t, int indent);
void print_stmt(const Texp& t, int indent);
std::string str_indent(int indent);

void print_stmt(const Texp& t, int indent) {
  print(str_indent(indent));
  if ("do" == t.value)
    {
      print_do(t, indent + 1);
    }
  else if ("if" == t.value)
    {
      print("(if ", t[0].paren(), " ");
      print_do(t[1], indent + 1);
      println(")");
    }
  else if ("return-void" == t.value)
    {
      println("(return-void)");
    }
  else
    {
      println(t.paren());
    }
}

void print_do(const Texp& t, int indent) {
  println("(do ");
  for (const auto& child : t) {
    print_stmt(child, indent);
  }
  print(str_indent(indent - 1), ")");
}

// indent size 2
auto str_indent(int indent) -> std::string {
  std::string acc = "";
  for (int i = 0; i < indent; ++i)
    acc += "  "; // < set indent size
  return acc;
}

// print toplevels
// TODO: use matcher proof with format-config
// - format-config should have grammar in it
void print_program(const Texp& program) {

  for (const auto& child : program) {
    println();  // newline between each toplevel

    // (def name params return-type do)
    if ("def" == child.value) {
      print("(def ", child[0].paren(), " ", child[1].paren(), " ", child[2].paren(), " ");
      print_do(child[3], 1);
      println(")");
      continue;
    }

    if ("decl" == child.value) {
      println(child.paren());
      continue;
    }

    if ("str-table" == child.value) {
      println(child.paren());
      continue;
    }

    if ("struct" == child.value) {
      println(child.paren());
      continue;
    }
  }
}

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
