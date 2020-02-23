#include <iostream>
#include <string>

#include "magic_io.h"

using namespace magic_io;

struct User {
  std::string name;
  std::string status;
  uint64_t age;
};

int main() {
  User user = {
      "Ruslan",
      "I am okay.",
      23,
  };
  std::cout << user << std::endl;
  return 0;
}
