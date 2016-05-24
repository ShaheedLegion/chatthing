#include "core/core.h"
#include "core/screen.h"

namespace core {
States *States::instance = nullptr;

States::States() : currentState(0) {}
States *States::getInstance() {
  if (instance == nullptr)
    instance = new States();

  return instance;
}

States::~States() {
  print("Deleting states.");

  for (int i = 0; i < states.size(); ++i)
    delete states[i];
}

void States::addScreen(Screen *screen) { states.push_back(screen); }
void States::setWindow(sf::RenderWindow *w) {
  window = w;
  initialWidth = window->getSize().x;
  initialHeight = window->getSize().y;
  scaleX = 1.f;
  scaleY = 1.f;
}

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

void States::render(sf::Clock &clock) {
  if (states.empty())
    return;

  if (currentState < 0 || currentState > states.size())
    return;

  sf::Int32 elapsed = clock.getElapsedTime().asMilliseconds();
  states[currentState]->render(elapsed, window);
  clock.restart();
}

void States::resized() {
  // figure out the new scale
  scaleX = static_cast<float>(initialWidth) /
           static_cast<float>(window->getSize().x);
  scaleY = static_cast<float>(initialHeight) /
           static_cast<float>(window->getSize().y);
}

void States::getMousePos(std::pair<float, float> &p) {

  float x = sf::Mouse::getPosition(*window).x * scaleX;
  float y = sf::Mouse::getPosition(*window).y * scaleY;

  p.first = x;
  p.second = y;
}

void States::signalNextScreen() {
  // We could do wrap around on this, or add more complex logic.
  if (states.empty())
    return;

  if (++currentState > states.size() - 1)
    currentState = 0;
}

void States::handleKey(sf::Keyboard::Key key) {
  if (states.empty())
    return;

  if (currentState < 0 || currentState > states.size())
    return;

  states[currentState]->handleKey(key);
}

} // namespace core