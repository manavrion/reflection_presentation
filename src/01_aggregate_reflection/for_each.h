#include <experimental/compiler>
#include <experimental/meta>

namespace magic_io {
namespace meta = std::experimental::meta;
}
namespace magic_io::detail {

// clang-format off
template <typename T, typename Func>
void for_each_by_members(T&& t, Func&& f) {
  template for (auto&& member : t) {
    f(member);
  }
}
// clang-format on

}  // namespace magic_io::detail
