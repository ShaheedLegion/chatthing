#ifndef _CORE_SCREEN_
#define _CORE_SCREEN_

#include <SFML/Graphics.hpp>

namespace core {

class ISignalHelper;

class Screen {
protected:
  ISignalHelper *helper;

public:
  Screen(ISignalHelper *h) : helper(h) {}

  virtual void handleKey(sf::Keyboard::Key key) = 0;
  virtual void render(sf::Int32 elapsed, sf::RenderWindow *window) = 0;
};
}
#endif // _CORE_SCREEN_