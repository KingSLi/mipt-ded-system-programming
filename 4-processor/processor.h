#pragma once

#include <vector>
#include <stack>

#include "registers.h"
#include "commands.h"
#include "file_buffer.h"



class Processor{
 public:
  Processor(size_t ram_size=10) {
    ram.resize(ram_size, 0);
  }
  void SetProgram(std::vector<Instruct>&& instr);
  std::vector<Instruct>& GetProgram();
  void Implementation();

 private:
  std::vector<int> ram;
  std::stack<int> stack;
  Registers registers;

  std::vector<Instruct> instruction{};
};

void Processor::SetProgram(std::vector<Instruct>&& instr) {
  instruction = std::move(instr);
}

std::vector<Instruct>& Processor::GetProgram() {
  return instruction;
}

void Processor::Implementation() {
  for (size_t ipoint = 0; ipoint < instruction.size(); ++ipoint) {
    Commands::do_command[instruction[ipoint].cmd](instruction[ipoint].args, ram, stack, registers, ipoint);
  }
}
