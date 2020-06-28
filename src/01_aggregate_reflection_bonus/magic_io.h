#include <boost/pfr/detail/tie_from_structure_tuple.hpp>
#include <iostream>

#include "for_each.h"

template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

namespace magic_io::magic {
using boost::pfr::detail::tie_as_tuple;
}  // namespace magic_io::magic

namespace magic_io {

template <typename Char, typename Traits, typename T>
auto& operator<<(std::basic_ostream<Char, Traits>& out, const T& value) {
  out << '{';
  detail::for_each_by_members(
      value, overloaded{[&](auto&& arg) { out << arg << ", "; },
                        [&](const std::basic_string<Char, Traits>& arg) {
                          out << "\"" << arg << "\", ";
                        }});
  out << '}';
  return out;
}

}  // namespace magic_io
