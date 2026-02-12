#include "engine.hpp"
#include "TitleScene.hpp"

int main(int argc, char** argv) {
    Engine& engine = Engine::instance();

    TitleScene titleScene;
    engine.setScene(&titleScene);
    engine.run();
    engine.shutdown();

}