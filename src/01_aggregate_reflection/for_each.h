#include <experimental/compiler>
#include <experimental/meta>

namespace magic_io {
namespace meta = std::experimental::meta;
}
namespace magic_io::detail {

// clang-format off
template <typename T, typename Func>
void for_each_by_members(T&& t, Func&& f) {
  consteval {
    meta::info info = reflexpr(std::decay_t<T>);
    auto range = meta::data_member_range(info);
    for (meta::info member : range) {
      if (meta::is_nonstatic_data_member(member)) {
        -> __fragment {
          f(std::forward<T>(t).*valueof(member));
        };
      }
    }
  }
}
// clang-format on

}  // namespace magic_io::detail
