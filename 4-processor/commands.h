#ifndef INC_4_PROCESSOR_COMMANDS_H_H
#define INC_4_PROCESSOR_COMMANDS_H_H

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <functional>
#include <cmath>

#define binary_operator_for_stack(operation)  \
  int x = stack.top(); stack.pop();           \
  int y = stack.top(); stack.pop();           \
  stack.push(y operation x);                  \

#define memory std::string& arguments, std::vector<int>& ram, std::stack<int>& stack, Registers& registers
#define memory_types std::string&, std::vector<int>&, std::stack<int>&, Registers&


struct Instruct{
  int cmd;
  std::string args;
};

namespace Commands{
  enum Command{
    Push,
    Pop,
    Add,
    Sub,
    Mul,
    Div,
    In,
    Out,
    Sqrt,
    Jmp,
    Je
  };

  std::map<std::string, Command> match{
          {"push", Push},
          {"pop", Pop},
          {"add", Add},
          {"sub", Sub},
          {"mul", Mul},
          {"div", Div},
          {"in", In},
          {"out", Out},
          {"sqrt", Sqrt},
          {"jmp", Jmp},
          {"je", Je},
  };

  std::vector<std::string> reverse_match{"push", "pop", "add", "sub", "mul", "div",
                                         "in", "out", "sqrt", "jmp", "je"};

  std::vector<std::function<void(memory_types, size_t&)>> do_command{
          [] (memory, size_t& instr_p) { // push
              // check argumentsf
              if (arguments[0] == '[') {
                stack.push(ram[static_cast<int>(arguments[1] - '0')]);
              } else if (arguments[0] == 'r') {
                stack.push(registers.get(arguments));
              } else if (std::isdigit(arguments[0]) ||
                      (arguments[0] == '-' && std::isdigit(arguments[1]))) {
                stack.push(std::stoi(arguments));
              } else {
                //error
              }
          },
          [] (memory, size_t& instr_p) { // pop
              if (arguments[0] == '[') {
                ram[static_cast<int>(arguments[1] - '0')] = stack.top();
              } else if (arguments[0] == 'r') {
                registers.set(arguments, stack.top());
              } else if (arguments.size() != 0) {
                //error
              }
              stack.pop();
          },
          [] (memory, size_t& instr_p) { binary_operator_for_stack(+) }, // add
          [] (memory, size_t& instr_p) { binary_operator_for_stack(-) }, // sub
          [] (memory, size_t& instr_p) { binary_operator_for_stack(*) }, // mul
          [] (memory, size_t& instr_p) { binary_operator_for_stack(/) }, // div
          [] (memory, size_t& instr_p) { // in
              int tmp;
              std::cin >> tmp;
              stack.push(tmp);
          },
          [] (memory, size_t& instr_p) { // out
              std::cout << stack.top() << " ";
          },
          [] (memory, size_t& instr_p) { // sqrt
              int tmp = stack.top();
              stack.pop();
              stack.push(static_cast<int>(sqrt(static_cast<double>(tmp))));
          },
          [] (memory, size_t& instr_p) { // jmp
              size_t point_to_jump = static_cast<size_t>(std::stoi(arguments)) - 1;
              instr_p = point_to_jump;
          },
          [] (memory, size_t& instr_p) { // je
              int x = stack.top(); stack.pop();
              int y = stack.top(); stack.pop();
              if (x == y) {
                size_t point_to_jump = static_cast<size_t>(std::stoi(arguments)) - 1;
                instr_p = point_to_jump;
              }
              stack.push(y);
              stack.push(x);
          }

  };
};

#endif //INC_4_PROCESSOR_COMMANDS_H_H
