#include <SFML/Graphics.hpp>
#include "core/core.h"
#include "core/screen.h"

// Include the screens we are going to use for this game.
#include "app/intro_screen.h"
#include "app/game_screen.h"

int main() {
  core::print("Starting up.");

  // Request a 24-bits depth buffer when creating the window
  sf::ContextSettings contextSettings(24);

  core::print("Creating window");

  // Create the main window
  sf::RenderWindow window(sf::VideoMode(800, 600), "SpaceThing",
                          sf::Style::Default, contextSettings);

  window.setVerticalSyncEnabled(true);
  core::print("Enabling window.");
  window.setActive();
  core::print("Setting up core.");

  // Perform setup.
  core::States *states{core::States::getInstance()};
  states->setWindow(&window);
  states->addScreen(new app::IntroScreen(states, &window));
  states->addScreen(new app::GameScreen(states, &window));

  // Create a clock for measuring the time elapsed
  sf::Clock clock;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
          window.close();
        else
          states->handleKey(event.key.code);
      }
      if (event.type == sf::Event::Resized)
        states->resized();
    }

    window.clear();
    states->render(clock);
    window.display();
  }

  // Don't forget to delete our singleton
  delete core::States::getInstance();

  return EXIT_SUCCESS;
}
