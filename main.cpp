#include "engine.hpp"
#include "TitleScene.hpp"

int main(int argc, char** argv) {
    // Start engine singleton and boot into title scene.
    Engine& engine = Engine::instance();

    TitleScene titleScene;
    engine.setScene(&titleScene);
    engine.run();
    engine.shutdown();

    return 0;
}
