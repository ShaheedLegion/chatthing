#ifndef _APP_LOGIN_SCREEN_
#define _APP_LOGIN_SCREEN_

#include "core/screen.h"

namespace app {

class LoginScreen : public core::Screen {
public:
  LoginScreen(core::ISignalHelper *helper, tgui::Gui &g);
  ~LoginScreen();

  virtual void addWidgets() override;
  virtual void hideWidgets() override;
  virtual void handleCallbacks() override;
};
}
#endif // _APP_LOGIN_SCREEN_