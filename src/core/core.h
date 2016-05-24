#ifndef _CORE_LIB_
#define _CORE_LIB_

#define CORE_VERSION_MAJOR 1
#define CORE_VERSION_MINOR 0

#include <iostream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "core/defs.h"

namespace core {
// Easy way to print without having to muck with namespaces and endl.
static void print(const std::string &output) {
  std::cout << output.c_str() << std::endl;
}

static void print_int(int v) { std::cout << v << std::endl; }
static void print_float(float v) { std::cout << v << std::endl; }

class ISignalHelper {
public:
  virtual void signalNextScreen() = 0;
};

// This class is a singleton.
class States : public ISignalHelper {
private:
  static States *instance;
  std::vector<Screen *> states;
  std::map<std::string, sf::Texture> textures;
  std::map<std::string, sf::Font> fonts;
  int currentState;
  int initialWidth;
  int initialHeight;
  float scaleX;
  float scaleY;
  sf::RenderWindow *window;

  States();

public:
  static States *getInstance();

  // Be very careful when you delete this.
  ~States();

  void setWindow(sf::RenderWindow *w);
  void resized();

  float getScaleX() const { return scaleX; }
  float getScaleY() const { return scaleY; }

  void getMousePos(std::pair<float, float> &p);

  void addTexture(const std::string &path);
  sf::Texture &getTexture(const std::string &path);

  void addFont(const std::string &path);
  sf::Font &getFont(const std::string &path);

  void addScreen(Screen *screen);

  void render(sf::Clock &clock);

  virtual void signalNextScreen() override;
  void handleKey(sf::Keyboard::Key key);
};
} // namespace core

#endif // _CORE_LIB_