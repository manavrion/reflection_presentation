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
  constexpr auto range = meta::range(reflexpr(std::decay_t<T>));
  template for (constexpr auto member : range) {
    if (meta::is_nonstatic_data_member(member)) {
      op(t.idexpr(member), meta::name_of(member));
    }
  }
}
// clang-format on

}  // namespace magic_io::detail
