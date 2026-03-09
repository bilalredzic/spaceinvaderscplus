#include "Engine.hpp"
#include "TitleScene.hpp"

int main() {
    // Start engine singleton and boot into title scene.
    Engine& engine = Engine::instance();

    // Create the initial scene objects used to boot the game.
    TitleScene titleScene;
    engine.setScene(&titleScene);
    // Run the main loop until SDL quit is requested, then shut down cleanly.
    engine.run();
    engine.shutdown();

    return 0;
}
