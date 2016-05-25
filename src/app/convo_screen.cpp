#include "app/convo_screen.h"
#include "core/core.h"

namespace app {

ConvoScreen::~ConvoScreen() {}

ConvoScreen::ConvoScreen(core::ISignalHelper *helper, tgui::Gui &g)
    : core::Screen(helper, g) {}

void ConvoScreen::addWidgets() {}
void ConvoScreen::hideWidgets() {}
}
