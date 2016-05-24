#ifndef _APP_GAME_SCREEN_
#define _APP_GAME_SCREEN_

#include "core/screen.h"

namespace app {

class GameScreen;

class StarFieldPlanes {
  struct pos {
    float x;
    float y;
    float z;
    float s;
    int tx;
    int ty;
  };

private:
  friend class GameScreen;
  std::vector<std::vector<pos>> planes;

public:
  StarFieldPlanes(int numPlanes, int numStars);
  void update(int w, int h);

  std::vector<std::vector<pos>> &getStarPlanes() { return planes; }
};

class GameScreen : public core::Screen {

  sf::Text text;
  sf::Sprite player;
  StarFieldPlanes planes;

public:
  GameScreen(core::ISignalHelper *helper, sf::RenderWindow *window);
  ~GameScreen();

  virtual void handleKey(sf::Keyboard::Key key) override;
  virtual void render(sf::Int32 elapsed, sf::RenderWindow *window) override;
};
}
#endif // _APP_GAME_SCREEN_