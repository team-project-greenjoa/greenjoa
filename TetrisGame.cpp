#include "TetrisGame.h"

#include <iostream>
#include <limits>

namespace tetris {

TetrisGame::TetrisGame(TetrisView& view, IInputProvider& input, IBlockGenerator& blockGenerator)
    : view_(view), input_(input), blockGenerator_(blockGenerator) {}

void TetrisGame::run() {
    view_.showLogo(input_, stageRepository_);
    while (true) {
        resetGameState();
        stats_.setLevel(readStartLevel() - 1);
        startRound();
        runRoundLoop();
        view_.showGameOver();
        input_.waitForAnyKey();
        view_.clearScreen();
    }
}

void TetrisGame::resetGameState() {
    board_.reset();
    stats_.reset();
    gameOver_ = false;
}

int TetrisGame::readStartLevel() {
    int level = 0;
    view_.showStartGuide();
    while (level < constants::kSelectableMinLevel || level > constants::kSelectableMaxLevel) {
        view_.showLevelPrompt();
        std::cin >> level;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(constants::kInputBufferIgnoreSize, '\n');
            level = 0;
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    view_.clearScreen();
    return level;
}

void TetrisGame::startRound() {
    view_.showBoard(board_, stats_.getLevel());
    currentBlock_ = createSpawnBlock(blockGenerator_.makeNextShape(currentStage()));
    nextShape_ = blockGenerator_.makeNextShape(currentStage());
    view_.showNextBlock(nextShape_, stats_.getLevel());
    view_.showGameStats(stats_, currentStage(), true);
    view_.showCurrentBlock(currentBlock_);
}

void TetrisGame::runRoundLoop() {
    int tick = 1;
    while (!gameOver_) {
        if (input_.hasKey()) {
            handleInput(input_.readKey());
        }

        if (!gameOver_ && tick % currentStage().getSpeed() == 0) {
            gameOver_ = moveCurrentBlockDown() == MoveResult::GameOver;
        }

        if (!gameOver_) {
            updateStageIfNeeded();
            view_.moveCursorOutOfGameArea();
            view_.sleep(constants::kGameLoopSleepMs);
            ++tick;
        }
    }
}

void TetrisGame::handleInput(GameKey key) {
    switch (key) {
        case GameKey::Rotate:
            rotateCurrentBlock();
            break;
        case GameKey::Left:
            moveCurrentBlockHorizontally(-1);
            break;
        case GameKey::Right:
            moveCurrentBlockHorizontally(1);
            break;
        case GameKey::Down:
            gameOver_ = moveCurrentBlockDown() == MoveResult::GameOver;
            break;
        case GameKey::Drop:
            hardDropCurrentBlock();
            break;
        case GameKey::None:
        case GameKey::Any:
            break;
    }
}

MoveResult TetrisGame::moveCurrentBlockDown() {
    view_.eraseCurrentBlock(currentBlock_);
    currentBlock_.moveBy(0, 1);
    if (!board_.isCollision(currentBlock_)) {
        view_.showCurrentBlock(currentBlock_);
        return MoveResult::Moved;
    }

    currentBlock_.moveBy(0, -1);
    if (currentBlock_.getPosition().y <= 0) {
        return MoveResult::GameOver;
    }

    lockCurrentBlockAndSpawnNext();
    return MoveResult::Locked;
}

void TetrisGame::moveCurrentBlockHorizontally(int deltaX) {
    view_.eraseCurrentBlock(currentBlock_);
    currentBlock_.moveBy(deltaX, 0);
    if (board_.isCollision(currentBlock_)) {
        currentBlock_.moveBy(-deltaX, 0);
    }
    view_.showCurrentBlock(currentBlock_);
}

void TetrisGame::rotateCurrentBlock() {
    view_.eraseCurrentBlock(currentBlock_);
    currentBlock_.rotateClockwise();
    if (board_.isCollision(currentBlock_)) {
        currentBlock_.setRotation(currentBlock_.getRotation() - 1);
    }
    view_.showCurrentBlock(currentBlock_);
}

void TetrisGame::hardDropCurrentBlock() {
    MoveResult result = MoveResult::Moved;
    while (result == MoveResult::Moved) {
        result = moveCurrentBlockDown();
    }
    gameOver_ = result == MoveResult::GameOver;
    if (!gameOver_) {
        view_.showCurrentBlock(currentBlock_);
    }
}

void TetrisGame::lockCurrentBlockAndSpawnNext() {
    board_.merge(currentBlock_);
    const int clearedLineCount = board_.clearFullLines();
    if (clearedLineCount > 0) {
        stats_.addLines(clearedLineCount);
        addLineClearScore(clearedLineCount);
    }
    view_.showBoard(board_, stats_.getLevel());
    currentBlock_ = createSpawnBlock(nextShape_);
    nextShape_ = blockGenerator_.makeNextShape(currentStage());
    view_.showNextBlock(nextShape_, stats_.getLevel());
    view_.showGameStats(stats_, currentStage(), false);
    view_.showCurrentBlock(currentBlock_);
}

void TetrisGame::updateStageIfNeeded() {
    if (stats_.getLinesInCurrentStage() < currentStage().getClearLineGoal()) {
        return;
    }
    if (stats_.getLevel() < stageRepository_.getLastStageIndex()) {
        stats_.nextLevel();
        stats_.resetStageLines();
        view_.showBoard(board_, stats_.getLevel());
        view_.showNextBlock(nextShape_, stats_.getLevel());
        view_.showGameStats(stats_, currentStage(), false);
    }
}

void TetrisGame::addLineClearScore(int clearedLineCount) {
    for (int i = 0; i < clearedLineCount; ++i) {
        stats_.addScore(constants::kScoreBase + (stats_.getLevel() * constants::kScorePerLevel) +
                        blockGenerator_.nextScoreBonus(constants::kScoreRandomBonusExclusive));
    }
}

Tetromino TetrisGame::createSpawnBlock(TetrominoShape shape) const {
    return Tetromino{shape, 0, {constants::kStartBlockX, constants::kStartBlockY}};
}

const StageConfig& TetrisGame::currentStage() const { return stageRepository_.getStage(stats_.getLevel()); }

}  // namespace tetris
