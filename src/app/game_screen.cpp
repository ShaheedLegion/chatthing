#include "app/game_screen.h"
#include "core/core.h"

namespace app {

const std::string font_name = "resources/sansation.ttf";
const std::string ship_name = "resources/sprites/player1.png";

GameScreen::~GameScreen() {}

GameScreen::GameScreen(core::ISignalHelper *helper, sf::RenderWindow *window)
    : core::Screen(helper), planes(3, 100) {
  core::States *states{core::States::getInstance()};

  states->addTexture(ship_name);
  player = sf::Sprite(states->getTexture(ship_name));
}

StarFieldPlanes::StarFieldPlanes(int numPlanes, int numStars) {
  srand(static_cast<unsigned int>(2635));

  for (int j = 0; j < numPlanes; j++) {

    std::vector<pos> vec;
    for (int i = 0; i < numStars; ++i) {
      pos p{
          ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 70.f) -
              35.f,
          ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 70.f) -
              35.f,
          static_cast<float>((100.f / static_cast<float>(numPlanes)) *
                             static_cast<float>(j + 1.f)),
          0.f, 0, 0};
      p.s = (p.z * 0.001f) + .2f;

      vec.push_back(p);
    }
    planes.push_back(vec);
  }
}

void StarFieldPlanes::update(int w, int h) {
  for (int k = 0; k < planes.size(); k++) {
    unsigned int kPlaneSize{planes[k].size()};
    for (int i = 0; i < kPlaneSize; ++i) {
      pos &p{planes[k][i]};

      p.y += p.s;

      // perspective projection.
      p.tx = (p.x / p.z) * w + (w >> 1);
      p.ty = (p.y / p.z) * h + (h >> 1);

      // clamp the star.
      if (p.tx < 10 || p.tx > w) {
        p.tx = 2;
        p.x = ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) *
               70.f) -
              35.f;
      }

      if (p.ty > h) {
        p.ty = 2;
        p.y = ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) *
               37.f) -
              50.f;
        p.x = ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) *
               70.f) -
              35.f;
      }
    }
  }
}

// Do input processing here - other actions cause migration to next screen.
void GameScreen::handleKey(sf::Keyboard::Key key) {
  // if (helper != nullptr)
  //  helper->signalNextScreen();
}

void GameScreen::render(sf::Int32 elapsed, sf::RenderWindow *window) {

  std::pair<float, float> p;
  core::States::getInstance()->getMousePos(p);
  player.setPosition(p.first, p.second);

  planes.update(window->getSize().x, window->getSize().y);

  // background.setColor(sf::Color());
  // define a circle with radius = 200
  sf::CircleShape circle(3);
  circle.setFillColor(sf::Color(255, 255, 255, 128));

  for (auto &j : planes.getStarPlanes()) {
    std::vector<StarFieldPlanes::pos> &stars{j};
    for (auto star : stars) {
      circle.setRadius(3 - static_cast<int>(star.z / 50));
      sf::Uint8 c = 255 - static_cast<int>(star.z);
      circle.setFillColor(sf::Color(c, c, c, c));
      circle.setPosition(static_cast<float>(star.tx),
                         static_cast<float>(star.ty));
      window->draw(circle);
    }
  }
  window->draw(player);
}
}
