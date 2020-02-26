#pragma once

#include <experimental/compiler>
#include <experimental/meta>
#include <utility>

namespace magic_io {
namespace meta = std::experimental::meta;
}

namespace magic_io::detail {

// clang-format off
template<class T, class Operator>
void for_each_by_members(T&& t, Operator&& op) {
  consteval {
    auto info = reflexpr(std::decay_t<T>);
    auto range = meta::data_member_range(info);
    for (auto member : range)
      if (meta::is_nonstatic_data_member(member))
      -> __fragment {
        op(t.*valueof(member), meta::name_of(member));
      };
  }
}
// clang-format on

}  // namespace magic_io::detail
