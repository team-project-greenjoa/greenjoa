#ifndef TETRIS_VIEW_H
#define TETRIS_VIEW_H

#include "Board.h"
#include "GameStats.h"
#include "IInputProvider.h"
#include "IRenderer.h"
#include "Stage.h"

namespace tetris {

class TetrisView {
public:
    explicit TetrisView(IRenderer& renderer);

    void showLogo(IInputProvider& input, const StageRepository& stages);
    void showStartGuide();
    void showLevelPrompt();
    void showBoard(const Board& board, int level);
    void showCurrentBlock(const Tetromino& block);
    void eraseCurrentBlock(const Tetromino& block);
    void showNextBlock(TetrominoShape shape, int level);
    void showGameStats(const GameStats& stats, const StageConfig& stage, bool printLabels);
    void showLineClearAnimation(int row);
    void showGameOver();
    void moveCursorOutOfGameArea();
    void sleep(int milliseconds);
    void clearScreen();

private:
    void drawBlockCells(const Tetromino& block, const std::string& cellText);
    void printAt(int x, int y, const std::string& text);
    Position toScreenPosition(int boardX, int boardY) const;

    IRenderer& renderer_;
    Position boardOffset_{constants::kDefaultBoardOffsetX, constants::kDefaultBoardOffsetY};
};

}  // namespace tetris

#endif  // TETRIS_VIEW_H
