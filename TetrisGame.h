#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "Board.h"
#include "GameStats.h"
#include "IBlockGenerator.h"
#include "IInputProvider.h"
#include "Stage.h"
#include "TetrisView.h"

namespace tetris {

enum class MoveResult {
    Moved,
    Locked,
    GameOver,
};

class TetrisGame {
public:
    TetrisGame(TetrisView& view, IInputProvider& input, IBlockGenerator& blockGenerator);

    void run();

private:
    void resetGameState();
    int readStartLevel();
    void startRound();
    void runRoundLoop();
    void handleInput(GameKey key);
    MoveResult moveCurrentBlockDown();
    void moveCurrentBlockHorizontally(int deltaX);
    void rotateCurrentBlock();
    void hardDropCurrentBlock();
    void lockCurrentBlockAndSpawnNext();
    void updateStageIfNeeded();
    void addLineClearScore(int clearedLineCount);
    Tetromino createSpawnBlock(TetrominoShape shape) const;
    const StageConfig& currentStage() const;

    TetrisView& view_;
    IInputProvider& input_;
    IBlockGenerator& blockGenerator_;
    StageRepository stageRepository_;
    Board board_;
    GameStats stats_;
    Tetromino currentBlock_{TetrominoShape::I};
    TetrominoShape nextShape_ = TetrominoShape::I;
    bool gameOver_ = false;
};

}  // namespace tetris

#endif  // TETRIS_GAME_H
