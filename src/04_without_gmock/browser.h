#pragma once
#include "mockable.h"

namespace browser {

struct Base {
  void BaseInit() {}
};

struct MOCKABLE Tab : public Base {
  int Init() {
    return 42;
  }
  int Init(int&& i) {
    return 42;
  }
  int Init(const int& i) {
    return 42;
  }
};

struct Browser {
  void AddTab(Tab tab) {
    tab.BaseInit();
    int i = tab.Init();
  }
};

}  // namespace browser
