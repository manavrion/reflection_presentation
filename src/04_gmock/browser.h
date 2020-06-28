#pragma once
#include <gmock/gmock.h>

namespace browser {

struct ITab {
  virtual void Init() = 0;
  virtual ~ITab() = default;
};

struct Tab : public ITab {
  void Init() final {}
};

struct MockTab : public ITab {
  MOCK_METHOD(void, Init, (), (override));
};

struct Browser {
  void AddTab(ITab* tab) { tab->Init(); }
};

struct BadBrowser {
  void AddTab(ITab* tab) {}
};

}  // namespace browser
