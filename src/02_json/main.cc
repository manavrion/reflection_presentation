#include <iostream>
#include <nlohmann/json.hpp>

struct User {
  std::string name;
  std::string status;
  int age;
};

void to_json(nlohmann::json& json, const User& user) {
  json["name"] = user.name;
  json["status"] = user.status;
  json["age"] = user.age;
}

void from_json(const nlohmann::json& json, User& user) {
  json.at("name").get_to(user.name);
  json.at("status").get_to(user.status);
  json.at("age").get_to(user.age);
}

int main() {
  User user = {
      "Ruslan",
      "I am okay.",
      23,
  };
  std::cout << nlohmann::json(user) << std::endl;
  return 0;
}
