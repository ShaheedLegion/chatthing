#ifndef _CORE_SCREEN_
#define _CORE_SCREEN_

#include <TGUI/TGUI.hpp>

namespace core {

class ISignalHelper;

class Screen {
protected:
  ISignalHelper *helper;
  tgui::Gui &gui;

public:
  Screen(ISignalHelper *h, tgui::Gui &g) : helper(h), gui(g) {}

  virtual void addWidgets() = 0;
  virtual void hideWidgets() = 0;
};
}
#endif // _CORE_SCREEN_