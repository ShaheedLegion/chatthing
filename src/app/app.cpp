#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "core/core.h"
#include "core/screen.h"

// Include the screens we are going to use for this game.
#include "app/convo_screen.h"
#include "app/covalent.hpp"
#include "app/login_screen.h"

#define W_W 1920
#define W_H 1080

void loadWidgets(tgui::Gui &gui) {
  tgui::Picture::Ptr picture(gui, "background");
  picture->load("resources/background.png");
  picture->setSize(W_W, W_H);
}

int main() {
  core::print("Starting up.");

  // Get the covalent info immediately - we can't move without it.
  app::CovalentInfo info;
  app::getCovalentInfo(info);
  if (!info.isValid) {
    core::print("Could not contact covalent:");
    core::print(info.msg);
    return 1;
  }

  core::print(info.msg);

  app::StartChatThread(info);

  // Request a 24-bits depth buffer when creating the window
  sf::ContextSettings contextSettings(24);

  core::print("Creating window");

  // Create the main window
  sf::RenderWindow window(sf::VideoMode(W_W, W_H), "ChatThing",
                          sf::Style::Default, contextSettings);
  tgui::Gui gui(window);
  window.setVerticalSyncEnabled(true);
  core::print("Enabling window.");
  window.setActive();
  core::print("Setting up core.");

  // We use our own resource manager.
  core::States *states{core::States::getInstance()};
  states->addFont("resources/sansation.ttf");
  gui.setGlobalFont(states->getFont("resources/sansation.ttf"));

  // Perform setup.
  loadWidgets(gui);

  states->addScreen(new app::LoginScreen(states, gui));
  states->addScreen(new app::ConvoScreen(states, gui));

  states->signalNextScreen();

  // We're not using SFML to render anything in this program, so reset OpenGL
  // states. Otherwise we wouldn't see anything.
  window.resetGLStates();

  // Create a clock for measuring the time elapsed
  sf::Clock clock;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      gui.handleEvent(event);

      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
          window.close();
        // else
        //  states->handleKey(event.key.code);
      }
      // if (event.type == sf::Event::Resized)
      //  states->resized();
    }

    // Update states with notification that it can poll callbacks.
    states->handleCallbacks();

    // Rendering.
    window.clear();
    gui.draw();
    window.display();

    // window.clear();
    // states->render(clock);
    // window.display();
  }

  // Don't forget to delete our singleton
  delete core::States::getInstance();

  return EXIT_SUCCESS;
}
