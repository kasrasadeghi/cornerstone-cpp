#pragma once
#include "parser.hpp"
#include "backbone.hpp"
#include "gen.hpp"
#include "matcher.hpp"
#include "print.hpp"
#include "io.hpp"
#include "config.hpp"

// TODO: don't delete comments and between statement spacing?

void print_do(const Texp& t, int indent);
void print_stmt(const Texp& t, int indent);
std::string str_indent(int indent);


void print_do(const Texp& t, int indent) {
  println("(do ");
  for (const auto& child : t) {
    print_stmt(child, indent);
  }
  print(str_indent(indent - 1), ")");
}


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

// indent size 2
auto str_indent(int indent) -> std::string {
  std::string acc = "";
  for (int i = 0; i < indent; ++i)
    acc += "  "; // < set indent size
  return acc;
}

void print_toplevel(const Texp& toplevel) {

  // (def name params return-type do)
  if ("def" == toplevel.value) {
    print("(def ", toplevel[0].paren(), " ", toplevel[1].paren(), " ", toplevel[2].paren(), " ");
    print_do(toplevel[3], 1);
    println(")");
    return;
  }

  if ("decl" == toplevel.value) {
    println(toplevel.paren());
    return;
  }

  if ("str-table" == toplevel.value) {
    println(toplevel.paren());
    return;
  }

  if ("struct" == toplevel.value) {
    println(toplevel.paren());
    return;
  }
}

// print toplevels
// TODO: use matcher proof with format-config
// - format-config should have grammar in it
void print_program(const Texp& program) {

  for (const auto& child : program) {
    println();  // newline between each toplevel
    print_toplevel(child);
  }
}
