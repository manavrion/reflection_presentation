#include <boost/pfr/detail/sequence_tuple.hpp>
#include <utility>

namespace magic_io::magic {
using boost::pfr::detail::sequence_tuple::get;
}

namespace magic_io::detail {

template <typename T, typename Func, size_t... Is>
constexpr void for_each_impl(T&& t, Func&& f, std::index_sequence<Is...>) {
  (..., f(magic::get<Is>(std::forward<T>(t))));
}

template <typename T, typename Func>
constexpr void for_each(T&& t, Func&& f) {
  for_each_impl(std::forward<T>(t), std::forward<Func>(f),
                std::make_index_sequence<std::decay_t<T>::size_v>{});
}

}  // namespace magic_io::detail
