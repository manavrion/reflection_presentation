#include <iostream>

#include "03_protobuf/protos/user.pb.h"

int main() {
  User user;
  user.set_name("Ruslan");
  user.set_status("I am okay.");
  user.set_age(23);

  std::cout << user.DebugString() << std::endl;
  return 0;
}
