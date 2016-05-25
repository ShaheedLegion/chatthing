#include "app/login_screen.h"
#include "core/core.h"

namespace app {

LoginScreen::~LoginScreen() {}

LoginScreen::LoginScreen(core::ISignalHelper *helper, tgui::Gui &g)
    : core::Screen(helper, g) {}

void LoginScreen::addWidgets() {
  int ww = static_cast<int>(gui.getSize().x);
  int wh = static_cast<int>(gui.getSize().y);

  // Stick everything in this UI into a panel
  tgui::Panel::Ptr panel1(gui, "login_panel"); // Add a panel to the gui
  panel1->setSize(ww, 300);
  panel1->setPosition(sf::Vector2f(0.f, 250.f));
  panel1->setBackgroundColor(sf::Color(100, 100, 100, 255));

  // Create the username label
  tgui::Label::Ptr labelUsername(*panel1);
  labelUsername->setText("Username:");
  labelUsername->setPosition(200, 40);

  // Create the password label
  tgui::Label::Ptr labelPassword(*panel1);
  labelPassword->setText("Password:");
  labelPassword->setPosition(200, 120);

  // Create the username edit box
  tgui::EditBox::Ptr editBoxUsername(*panel1, "Username");
  editBoxUsername->load("resources/black.conf");
  editBoxUsername->setSize(400, 40);
  editBoxUsername->setPosition(400, 40);

  // Create the password edit box (we will copy the previously created edit box)
  tgui::EditBox::Ptr editBoxPassword =
      (*panel1).copy(editBoxUsername, "Password");
  editBoxPassword->setPosition(400, 120);
  editBoxPassword->setPasswordCharacter('*');

  // Create the login button
  tgui::Button::Ptr button(*panel1);
  button->load("resources/black.conf");
  button->setSize(260, 60);
  button->setPosition(400, 200);
  button->setText("Login");
  button->bindCallback(tgui::Button::LeftMouseClicked);
  button->setCallbackId(2635);
}

// Not sure how to hide widgets at this point ...
void LoginScreen::hideWidgets() {
  auto panel = gui.get("login_panel");
  panel->hide();
}

void LoginScreen::handleCallbacks() {
  // The callback loop
  tgui::Callback callback;
  while (gui.pollCallback(callback)) {
    // Make sure tha callback comes from the button
    if (callback.id == 2635) {
      // Get the username and password
      tgui::EditBox::Ptr editBoxUsername = gui.get("Username", true);
      tgui::EditBox::Ptr editBoxPassword = gui.get("Password", true);

      sf::String username = editBoxUsername->getText();
      sf::String password = editBoxPassword->getText();

      // Continue here by checking if the username and password are correct ...
      core::print("Handled callback for login button:");
      core::print(username);
      core::print(password);

      if (username == "test" && password == "test") {
        helper->signalNextScreen();
      }
    }
  }
}
}