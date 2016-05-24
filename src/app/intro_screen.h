#ifndef _APP_INTRO_SCREEN_
#define _APP_INTRO_SCREEN_

#include "core/screen.h"

namespace app {

class IntroScreen;

class StarField {
  struct pos {
    float x;
    float y;
    float z;
    float s;
    int tx;
    int ty;
  };

private:
  friend class IntroScreen;
  std::vector<pos> stars;

public:
  StarField(int numStars);
  void update(int w, int h);

  std::vector<pos> &getStars() { return stars; }
};

class IntroScreen : public core::Screen {
  sf::Text text;
  StarField field;

public:
  IntroScreen(core::ISignalHelper *helper, sf::RenderWindow *window);
  ~IntroScreen();

  virtual void handleKey(sf::Keyboard::Key key) override;
  virtual void render(sf::Int32 elapsed, sf::RenderWindow *window) override;
};
}
#endif // _APP_INTRO_SCREEN_