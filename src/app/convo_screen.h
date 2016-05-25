#ifndef _APP_GAME_SCREEN_
#define _APP_GAME_SCREEN_

#include "core/screen.h"

namespace app {

class ConvoScreen : public core::Screen {
public:
  ConvoScreen(core::ISignalHelper *helper, tgui::Gui &g);
  ~ConvoScreen();

  virtual void addWidgets() override;
  virtual void hideWidgets() override;
};
}
#endif // _APP_GAME_SCREEN_