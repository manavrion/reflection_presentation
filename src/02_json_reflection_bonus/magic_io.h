#pragma once

#include <nlohmann/json.hpp>

#include "for_each.h"

namespace magic_io {

// clang-form at off
template <typename T>
void to_json(nlohmann::json& json, const T& t) {
  magic_io::detail::for_each_by_members(
      t, [&json, &t](auto& arg, auto name) { json[name] = arg; });
}

template <typename T>
void from_json(const nlohmann::json& json, T& t) {
  magic_io::detail::for_each_by_members(
      t, [&json, &t](auto& arg, auto name) { json.at(name).get_to(arg); });
}
// clang-form at on

}  // namespace magic_io
