#include <iostream>

#include "magic_io.h"

using magic_io::from_json;
using magic_io::to_json;

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
  std::cout << nlohmann::json(user) << std::endl;
  return 0;
}
