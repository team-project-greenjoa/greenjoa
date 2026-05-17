#include "TetrisGame.h"

#include <iostream>
#include <limits>
#include <vector>

namespace tetris {

TetrisGame::TetrisGame(TetrisView& view, IInputProvider& input, RandomBlockGenerator& blockGenerator)
    : view_(view), input_(input), blockGenerator_(blockGenerator) {}

void TetrisGame::run() {
    view_.showLogo(input_);
    while (true) {
        resetGameState();
        stageManager_.setLevel(readStartLevel() - 1);
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
    // Initial setup input is kept here to keep the project simple for an OOP class assignment.
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
    view_.showBoard(board_, stageManager_.getLevel());
    currentBlock_ = createSpawnBlock(blockGenerator_.makeNextShape(currentStage()));
    nextShape_ = blockGenerator_.makeNextShape(currentStage());
    view_.showNextBlock(nextShape_, stageManager_.getLevel());
    view_.showGameStats(stats_, stageManager_, true);
    view_.showCurrentBlock(currentBlock_);
}

void TetrisGame::runRoundLoop() {
    int tick = 1;
    while (!gameOver_) {
        bool shouldRenderCurrentBlock = false;
        if (input_.hasKey()) {
            shouldRenderCurrentBlock = handleInput(input_.readKey());
        }

        if (!gameOver_ && tick % currentStage().getSpeed() == 0) {
            const MoveResult result = moveCurrentBlockDown();
            gameOver_ = result == MoveResult::GameOver;
            shouldRenderCurrentBlock = shouldRenderCurrentBlock || result != MoveResult::GameOver;
        }

        if (!gameOver_) {
            updateStageIfNeeded();
            if (shouldRenderCurrentBlock) {
                view_.showCurrentBlock(currentBlock_);
            }
            view_.moveCursorOutOfGameArea();
            view_.sleep(constants::kGameLoopSleepMs);
            ++tick;
        }
    }
}

bool TetrisGame::handleInput(GameKey key) {
    switch (key) {
        case GameKey::Rotate:
            return rotateCurrentBlock();
        case GameKey::Left:
            return moveCurrentBlockHorizontally(-1);
        case GameKey::Right:
            return moveCurrentBlockHorizontally(1);
        case GameKey::Down: {
            const MoveResult result = moveCurrentBlockDown();
            gameOver_ = result == MoveResult::GameOver;
            return result != MoveResult::GameOver;
        }
        case GameKey::Drop:
            return hardDropCurrentBlock();
        case GameKey::None:
        case GameKey::Any:
            break;
    }
    return false;
}

MoveResult TetrisGame::moveCurrentBlockDown() {
    view_.eraseCurrentBlock(currentBlock_);
    currentBlock_.moveBy(0, 1);
    if (!board_.isCollision(currentBlock_)) {
        return MoveResult::Moved;
    }

    currentBlock_.moveBy(0, -1);
    if (currentBlock_.getPosition().y <= 0) {
        return MoveResult::GameOver;
    }

    lockCurrentBlockAndSpawnNext();
    return MoveResult::Locked;
}

bool TetrisGame::moveCurrentBlockHorizontally(int deltaX) {
    view_.eraseCurrentBlock(currentBlock_);
    currentBlock_.moveBy(deltaX, 0);
    if (board_.isCollision(currentBlock_)) {
        currentBlock_.moveBy(-deltaX, 0);
    }
    return true;
}

bool TetrisGame::rotateCurrentBlock() {
    view_.eraseCurrentBlock(currentBlock_);
    currentBlock_.rotateClockwise();
    if (board_.isCollision(currentBlock_)) {
        currentBlock_.setRotation(currentBlock_.getRotation() - 1);
    }
    return true;
}

bool TetrisGame::hardDropCurrentBlock() {
    MoveResult result = MoveResult::Moved;
    while (result == MoveResult::Moved) {
        result = moveCurrentBlockDown();
    }
    gameOver_ = result == MoveResult::GameOver;
    return !gameOver_;
}

void TetrisGame::lockCurrentBlockAndSpawnNext() {
    board_.merge(currentBlock_);
    const std::vector<int> fullLines = board_.findFullLines();
    if (!fullLines.empty()) {
        view_.showBoard(board_, stageManager_.getLevel());
    }
    for (int row : fullLines) {
        view_.showLineClearAnimation(row);
    }
    board_.clearLines(fullLines);

    const int clearedLineCount = static_cast<int>(fullLines.size());
    if (clearedLineCount > 0) {
        stats_.addLines(clearedLineCount);
        addLineClearScore(clearedLineCount);
    }
    view_.showBoard(board_, stageManager_.getLevel());
    currentBlock_ = createSpawnBlock(nextShape_);
    nextShape_ = blockGenerator_.makeNextShape(currentStage());
    view_.showNextBlock(nextShape_, stageManager_.getLevel());
    view_.showGameStats(stats_, stageManager_, false);
}

void TetrisGame::updateStageIfNeeded() {
    if (stats_.getLinesInCurrentStage() < currentStage().getClearLineGoal()) {
        return;
    }
    if (!stageManager_.isLastStage()) {
        stageManager_.levelUp();
        stats_.resetStageLines();
        view_.showBoard(board_, stageManager_.getLevel());
        view_.showNextBlock(nextShape_, stageManager_.getLevel());
        view_.showGameStats(stats_, stageManager_, false);
    }
}

void TetrisGame::addLineClearScore(int clearedLineCount) {
    for (int i = 0; i < clearedLineCount; ++i) {
        stats_.addScore(constants::kScoreBase + (stageManager_.getLevel() * constants::kScorePerLevel) +
                        blockGenerator_.nextScoreBonus(constants::kScoreRandomBonusExclusive));
    }
}

Tetromino TetrisGame::createSpawnBlock(TetrominoShape shape) const {
    return Tetromino{shape, 0, {constants::kStartBlockX, constants::kStartBlockY}};
}

const StageConfig& TetrisGame::currentStage() const { return stageManager_.currentStage(); }

}  // namespace tetris
