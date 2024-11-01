
#include "LongNumber.cpp"
#include <iostream>

// Nadoknada provjera 1
int main(int argc, char* argv[]) {
  LongNumber num1{5};
  std::cout << num1.value();
  LongNumber num2(num1);
  std::cout << num2.value();
  return 0;
}
