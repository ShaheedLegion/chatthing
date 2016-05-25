#ifndef _CORE_LIB_
#define _CORE_LIB_

#define CORE_VERSION_MAJOR 1
#define CORE_VERSION_MINOR 0

#include <SFML/Graphics.hpp>
#include "core/defs.h"
#include <iostream>
#include <map>
#include <vector>

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

  States();

public:
  static States *getInstance();

  // Be very careful when you delete this.
  ~States();

  void addTexture(const std::string &path);
  sf::Texture &getTexture(const std::string &path);

  void addFont(const std::string &path);
  sf::Font &getFont(const std::string &path);

  void addScreen(Screen *screen);

  virtual void signalNextScreen() override;
};
} // namespace core

#endif // _CORE_LIB_