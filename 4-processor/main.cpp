#include <cstdlib>
#include <iostream>
#include "processor.h"
#include "asssembler.h"

int main(int argc, char* argv[]) {
  std::string input_program;
  if (argc == 1) {
    input_program = "factorial_solver.txt";
  } else if (argc == 2) {
    freopen(argv[1], "r", stdin);
    getline(std::cin, input_program);
    fclose(stdin);
  } else {
    std::cout << "too many args";
    return 1;
  }
  Processor processor;
  processor.SetProgram(Assembler(input_program));
  processor.Implementation();
  DisAssembler(processor.GetProgram());
  return 0;
}