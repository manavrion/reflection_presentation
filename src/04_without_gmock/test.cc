#include <gtest/gtest.h>

#include "browser.h"

using namespace browser;

TEST(Test, MockTab) {
  Browser browser;
  auto tab = Tab::GetMockInstance();

  tab.ExpectAtLeastOneCallOf(METHOD(Tab, Init, int, ()));

  browser.AddTab(std::move(tab));
}

TEST(Test, Tab) {
  Tab tab;
  EXPECT_EQ(tab.Init(), 42);
}
