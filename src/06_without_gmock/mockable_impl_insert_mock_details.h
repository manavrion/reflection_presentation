#pragma once
#include <experimental/compiler>
#include <experimental/meta>

namespace meta = std::experimental::meta;

template <typename... Ts>
struct pack_t {};

template <typename R, typename... Args>
consteval void insert_mock(meta::info member, pack_t<Args...>) {
  ->__fragment struct T {
    R unqualid(meta::name_of(member))(Args... arg) {
      if (!this->_is_mocked) {
        return unqualid(meta::name_of(member),
                        "_impl")(std::forward<Args>(arg)...);
      }
      this->VisitMethod(
          static_cast<R (T::*)(Args...)>(&T::unqualid(meta::name_of(member))));
      return R();
    }
  };
}

template <typename R, typename... Args>
auto get_args(R (*ptr)(Args...)) -> pack_t<Args...>{};

template <typename T>
using get_args_v = decltype(get_args(std::declval<T>()));

consteval void insert_mock_details(meta::info member) {
  meta::info res_type = meta::return_type_of(member);

  ->__fragment struct {
    consteval {
      using value_t = decltype(valueof(member));
      using arg_pack_t = get_args_v<value_t>;
      using res_type_t = typename(res_type);
      insert_mock<res_type_t>(member, arg_pack_t{});
    }
  };

  meta::set_new_name(member, __concatenate(meta::name_of(member), "_impl"));
  ->member;
}