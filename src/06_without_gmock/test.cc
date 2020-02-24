#include <gtest/gtest.h>

#include "browser.h"

using namespace browser;

TEST(Test, Test) {
  Browser browser;
  auto tab = Tab::GetMockInstance();

  tab.ExpectAtLeastOneCallOf(METHOD(Tab, Init, int, ()));

  browser.AddTab(std::move(tab));
}
