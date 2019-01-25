#ifndef INC_4_PROCESSOR_REGISTERS_H
#define INC_4_PROCESSOR_REGISTERS_H

#include <string>

struct Registers{
  enum Register{
    RAX, RBX, RCX, RDX
  };

  Register detect_reg(std::string reg) {
    switch (reg[1]) {
      case 'a':  return RAX;
      case 'b':  return RBX;
      case 'c':  return RCX;
      case 'd':  return RDX;
    }
    // errror
  }

  void set(std::string& regist, int value) {
    registers[detect_reg(regist)] = value;
  }
  int get(std::string& regist) {
    return registers[detect_reg(regist)];
  }

 private:
  int registers[4] = {0, 0, 0, 0};
};

#endif //INC_4_PROCESSOR_REGISTERS_H
