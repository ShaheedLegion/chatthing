#include "core/core.h"
#include "core/screen.h"
#include <SFML/System.hpp>

namespace core {
States *States::instance = nullptr;

void covalentThread() {}

void netThread() {}

States::States()
    : currentState(-1), covalent(&covalentThread), network(&netThread) {
  covalent.launch();
  network.launch();
}

States *States::getInstance() {
  if (instance == nullptr)
    instance = new States();

  return instance;
}

States::~States() {
  print("Deleting states.");

  for (int i = 0; i < states.size(); ++i)
    delete states[i];

  print("Stopping threads.");
  covalent.terminate();
  network.terminate();
}

void States::addScreen(Screen *screen) { states.push_back(screen); }

void States::addTexture(const std::string &path) {
  if (textures.find(path) != textures.end())
    return;

  sf::Texture &tex = textures[path];
  tex.loadFromFile(path);
}
sf::Texture &States::getTexture(const std::string &path) {
  return textures[path];
}

void States::addFont(const std::string &path) {
  if (fonts.find(path) != fonts.end())
    return;

  sf::Font &font = fonts[path];
  font.loadFromFile(path);
}

sf::Font &States::getFont(const std::string &path) { return fonts[path]; }

void States::signalNextScreen() {
  if (states.empty())
    return;

  core::print("Moving to next state.");
  if (currentState >= 0 && currentState < states.size()) {
    states[currentState]->hideWidgets();
    core::print("Hiding initial state");
  }

  core::print("incrementing current state.");
  ++currentState;

  if (currentState >= 0 && currentState < states.size())
    states[currentState]->addWidgets();

  if (currentState > states.size() - 1) {
    currentState = 0;
    states[currentState]->addWidgets();
  }
}

void States::handleCallbacks() {
  if (states.empty())
    return;

  if (currentState >= 0 && currentState < states.size())
    states[currentState]->handleCallbacks();
}

} // namespace core