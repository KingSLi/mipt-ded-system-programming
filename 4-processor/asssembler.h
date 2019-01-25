//
// Created by maxim on 18.12.18.
//

#ifndef INC_4_PROCESSOR_ASSSEMBLER_H
#define INC_4_PROCESSOR_ASSSEMBLER_H

#include <iostream>
#include "commands.h"

std::vector<Instruct> Assembler(std::string& filename) {
  std::vector<Instruct> instruction{};
  FileBuffer buffer(filename.c_str());
  std::map<std::string, std::string> markers;
  for (int instructor_pointer = 0; instructor_pointer < buffer.countRows_; ++instructor_pointer) {
    std::string cmd{}, args{};
    int j = 0;
    if (buffer.pointers_[instructor_pointer][0] == '#') // comments
      continue;
    while (buffer.pointers_[instructor_pointer][j] != ' ' && buffer.pointers_[instructor_pointer][j] != '\0')
      cmd += buffer.pointers_[instructor_pointer][j++];
    while (buffer.pointers_[instructor_pointer][j] == ' ')
      j++;
    while (buffer.pointers_[instructor_pointer][j] != '\0')
      args += buffer.pointers_[instructor_pointer][j++];

    if (cmd == ":") {
      markers[args] = std::to_string(instruction.size());
      continue;
    }
    if (cmd == "")
      continue;
    if (cmd == "end")
      break;
    instruction.push_back({Commands::match[cmd], args});
  }

  for (auto& inst : instruction) {
    if (inst.cmd == Commands::Jmp || inst.cmd == Commands::Je)
      inst.args = markers[inst.args];
  }
  return instruction;
}

void DisAssembler(std::vector<Instruct>& instruction, std::string filename="disasm_program.txt") {
  freopen(filename.c_str(), "w", stdout);
  std::map<int, int> markers;
  for (int i = 0; i < instruction.size(); ++i) {
    if (instruction[i].cmd == 9 || instruction[i].cmd == 10)
      markers[atoi(instruction[i].args.c_str())] = atoi(instruction[i].args.c_str());
  }
  for (int i = 0; i < instruction.size(); ++i) {
    if (markers.find(i) != markers.end())
      std::cout << ": " << std::to_string(markers[i]) << std::endl;
    std::cout << Commands::reverse_match[instruction[i].cmd] << " " << instruction[i].args << std::endl;
  }
}



#endif //INC_4_PROCESSOR_ASSSEMBLER_H
