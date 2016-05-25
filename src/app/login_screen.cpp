#include "app/login_screen.h"
#include "core/core.h"

namespace app {

LoginScreen::~LoginScreen() {}

LoginScreen::LoginScreen(core::ISignalHelper *helper, tgui::Gui &g)
    : core::Screen(helper, g) {}

void LoginScreen::addWidgets() {
  int ww = static_cast<int>(gui.getSize().x);
  int wh = static_cast<int>(gui.getSize().y);

  // Create the username label
  tgui::Label::Ptr labelUsername(gui);
  labelUsername->setText("Username:");
  labelUsername->setPosition(200, 240);

  // Create the password label
  tgui::Label::Ptr labelPassword(gui);
  labelPassword->setText("Password:");
  labelPassword->setPosition(200, 320);

  // Create the username edit box
  tgui::EditBox::Ptr editBoxUsername(gui, "Username");
  editBoxUsername->load("resources/black.conf");
  editBoxUsername->setSize(400, 40);
  editBoxUsername->setPosition(400, 240);

  // Create the password edit box (we will copy the previously created edit box)
  tgui::EditBox::Ptr editBoxPassword = gui.copy(editBoxUsername, "Password");
  editBoxPassword->setPosition(400, 320);
  editBoxPassword->setPasswordCharacter('*');

  // Create the login button
  tgui::Button::Ptr button(gui);
  button->load("resources/black.conf");
  button->setSize(260, 60);
  button->setPosition(400, 440);
  button->setText("Login");
  // button->bindCallback(tgui::Button::LeftMouseClicked);
  // button->setCallbackId(1);
}

// Not sure how to hide widgets at this point ...
void LoginScreen::hideWidgets() {}
}
