#include <iostream>

#include "parseer.h"
#include "simplifier.h"
#include "printer.h"

int main(int argc, char* argv[]) {
  std::string expression;
  if (argc == 1) {
    expression = "(x + 5) / (x + 1) + log(cos(x^2 + 3))";
  } else if (argc == 2) {
    freopen(argv[1], "r", stdin);
    getline(std::cin, expression);
    fclose(stdin);
  } else {
    std::cout << "too many args";
    return 1;
  }
  freopen("output.txt", "w", stdout);
  auto parsed = parse_expression(expression);

  std::cout << "Исходное выражение f(x) = ";
  print_expression(parsed);
  std::cout << std::endl << std::endl;

  std::cout << "Производная от f,  f'(x) = ";
  auto diff = differentiation(parsed);
  simplify(diff);
  print_expression(diff);
  return 0;
}