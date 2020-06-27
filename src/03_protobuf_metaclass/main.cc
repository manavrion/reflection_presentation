#include <iostream>

#include "proto.h"

using magic_proto::proto_message;

struct(proto_message) User {
  //std::string name;
  //std::string status;
  int32_t age;
};

int main() {
  //User user;
  //user.set_name("Ruslan");
  //user.set_status("I am okay.");
  //user.set_age(23);

  //std::cout << user.DebugString() << std::endl;
  return 0;
}
