#pragma once
#include "mockable_impl_insert_mock_details.h"

template <typename T>
size_t address_of_method(T t) {
  return (size_t) reinterpret_cast<void *&>(t);
}

struct trigger_t {
  bool active = true;
  ~trigger_t() { assert(!active); }
};

consteval void mockable(meta::info info) {
  for (meta::info base : meta::base_spec_range(info)) {
    ->base;
  }
  for (meta::info member : meta::member_range(info)) {
    if (meta::is_member_function(member) &&
        !meta::is_special_member_function(member)) {
      insert_mock_details(member);
    } else {
      ->member;
    }
  }

  ->__fragment class T {
    bool _is_mocked = false;
    std::map<size_t, trigger_t> _map;

   public:
    template <typename... Args>
    static T GetMockInstance(Args &&... arg) {
      T result(std::forward<Args>(arg)...);
      result._is_mocked = true;
      return result;
    }

    template <typename D>
    void ExpectAtLeastOneCallOf(D t) {
      _map.emplace(std::piecewise_construct,
                   std::forward_as_tuple(address_of_method(t)),
                   std::forward_as_tuple());
    }

    template <typename D>
    void VisitMethod(D t) {
      _map.at(address_of_method(t)).active = false;
    }
  };
}
