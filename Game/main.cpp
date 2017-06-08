#include "EngineAssembler.h"
#include "Engine.h"

int main() {
    thirtythree::EngineAssembler engine_assembler;
    thirtythree::Engine *engine = engine_assembler.AssemblyEngine();
    engine->StartGame();
    return 0;
}
