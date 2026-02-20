#include "Engine.hpp"
#include "TitleScene.hpp"
#include "PlayScene.hpp"

int main(int argc, char** argv) {
    // Start engine singleton and boot into title scene.
    Engine& engine = Engine::instance();

    TitleScene titleScene;
    PlayScene playScene;
    engine.setScene(&playScene);
    engine.run();
    engine.shutdown();

    return 0;
}
