#include "ConsoleInput.h"
#include "ConsoleRenderer.h"
#include "RandomBlockGenerator.h"
#include "TetrisGame.h"
#include "TetrisView.h"

int main() {
    tetris::ConsoleRenderer renderer;
    tetris::ConsoleInput input;
    tetris::RandomBlockGenerator blockGenerator;
    tetris::TetrisView view(renderer);
    tetris::TetrisGame game(view, input, blockGenerator);
    game.run();
    return 0;
}
