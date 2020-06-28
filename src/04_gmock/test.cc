#include <gtest/gtest.h>

#include "browser.h"

using namespace browser;

TEST(Test, Browser) {
  Browser browser;
  MockTab tab;

  EXPECT_CALL(tab, Init()).Times(testing::AtLeast(1));

  browser.AddTab(&tab);
}

TEST(Test, BadBrowser) {
  BadBrowser browser;
  MockTab tab;

  EXPECT_CALL(tab, Init()).Times(0);

  browser.AddTab(&tab);
}