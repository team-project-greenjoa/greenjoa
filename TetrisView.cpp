#include "TetrisView.h"

#include <iomanip>
#include <sstream>

namespace tetris {
namespace {
constexpr const char* kFilledCell = "■";
constexpr const char* kEmptyCell = "  ";
constexpr const char* kBlinkCell = "□";
constexpr int kStatusLabelX = 35;
constexpr int kStatusValueX = 41;
constexpr int kCursorSafeX = 77;
constexpr int kCursorSafeY = 23;
}  // namespace

TetrisView::TetrisView(IRenderer& renderer) : renderer_(renderer) {}

void TetrisView::showLogo(IInputProvider& input, const StageRepository&) {
    printAt(13, 3, "┏━━━━━━━━━━━━━━━━━━━━━━━┓");
    renderer_.sleep(constants::kLogoSleepMs);
    printAt(13, 4, "┃◆◆◆  ◆◆◆  ◆◆◆   ◆◆     ◆   ◆◆◆ ┃");
    renderer_.sleep(constants::kLogoSleepMs);
    printAt(13, 5, "┃  ◆    ◆        ◆     ◆ ◆    ◆   ◆     ┃");
    renderer_.sleep(constants::kLogoSleepMs);
    printAt(13, 6, "┃  ◆    ◆◆◆    ◆     ◆◆     ◆     ◆   ┃");
    renderer_.sleep(constants::kLogoSleepMs);
    printAt(13, 7, "┃  ◆    ◆        ◆     ◆ ◆    ◆       ◆ ┃");
    renderer_.sleep(constants::kLogoSleepMs);
    printAt(13, 8, "┃  ◆    ◆◆◆    ◆     ◆  ◆   ◆   ◆◆◆ ┃");
    renderer_.sleep(constants::kLogoSleepMs);
    printAt(13, 9, "┗━━━━━━━━━━━━━━━━━━━━━━━┛");
    printAt(28, 20, "Please Press Any Key~!");
    renderer_.flush();
    input.waitForAnyKey();
    renderer_.clear();
}

void TetrisView::showStartGuide() {
    renderer_.setColor(ConsoleColor::Gray);
    printAt(10, 7, "┏━━━━<GAME KEY>━━━━━┓");
    printAt(10, 8, "┃ UP   : Rotate Block        ┃");
    printAt(10, 9, "┃ DOWN : Move One-Step Down  ┃");
    printAt(10, 10, "┃ SPACE: Move Bottom Down    ┃");
    printAt(10, 11, "┃ LEFT : Move Left           ┃");
    printAt(10, 12, "┃ RIGHT: Move Right          ┃");
    printAt(10, 13, "┗━━━━━━━━━━━━━━┛");
    renderer_.flush();
}


void TetrisView::showLevelPrompt() {
    renderer_.setColor(ConsoleColor::Gray);
    printAt(10, 3, "Select Start level[1-8]:       \b\b\b\b\b\b\b");
    renderer_.flush();
}

void TetrisView::showBoard(const Board& board, int level) {
    const auto& grid = board.getGrid();
    for (int row = 0; row < constants::kBoardRows; ++row) {
        for (int col = 0; col < constants::kBoardCols; ++col) {
            const bool wallOrFloor = col == constants::kLeftWallCol || col == constants::kRightWallCol ||
                                     row == constants::kBottomRow;
            renderer_.setColor(wallOrFloor ? static_cast<ConsoleColor>((level % 6) + 1) : ConsoleColor::DarkGray);
            const Position screen = toScreenPosition(col, row);
            printAt(screen.x, screen.y, grid[row][col] == 1 ? kFilledCell : kEmptyCell);
        }
    }
    renderer_.setColor(ConsoleColor::Black);
    moveCursorOutOfGameArea();
    renderer_.flush();
}

void TetrisView::showCurrentBlock(const Tetromino& block) {
    renderer_.setColor(block.getColor());
    drawBlockCells(block, kFilledCell);
    renderer_.setColor(ConsoleColor::Black);
    moveCursorOutOfGameArea();
    renderer_.flush();
}

void TetrisView::eraseCurrentBlock(const Tetromino& block) { drawBlockCells(block, kEmptyCell); }

void TetrisView::showNextBlock(TetrominoShape shape, int level) {
    renderer_.setColor(static_cast<ConsoleColor>(((level + 1) % 6) + 1));
    for (int row = 1; row < 7; ++row) {
        renderer_.moveCursor(constants::kPreviewBoxX, row);
        for (int col = 0; col < 6; ++col) {
            renderer_.write(row == 1 || row == 6 || col == 0 || col == 5 ? kFilledCell : kEmptyCell);
        }
    }
    showCurrentBlock(Tetromino{shape, 0, {constants::kPreviewBlockX, constants::kPreviewBlockY}});
}

void TetrisView::showGameStats(const GameStats& stats, const StageConfig& stage, bool printLabels) {
    renderer_.setColor(ConsoleColor::Gray);
    if (printLabels) {
        printAt(kStatusLabelX, 7, "STAGE");
        printAt(kStatusLabelX, 9, "SCORE");
        printAt(kStatusLabelX, 12, "LINES");
    }

    std::ostringstream scoreText;
    scoreText << std::setw(10) << stats.getScore();
    std::ostringstream remainingLineText;
    remainingLineText << std::setw(10) << (stage.getClearLineGoal() - stats.getLinesInCurrentStage());

    printAt(kStatusValueX, 7, std::to_string(stats.getLevel() + 1));
    printAt(kStatusLabelX, 10, scoreText.str());
    printAt(kStatusLabelX, 13, remainingLineText.str());
    renderer_.flush();
}

void TetrisView::showLineClearAnimation(int row) {
    renderer_.setColor(ConsoleColor::Blue);
    const Position start = toScreenPosition(constants::kPlayableLeftCol, row);
    renderer_.moveCursor(start.x, start.y);
    for (int col = constants::kPlayableLeftCol; col <= constants::kPlayableRightCol; ++col) {
        renderer_.write(kBlinkCell);
        renderer_.sleep(constants::kLineClearAnimationSleepMs);
    }
    renderer_.moveCursor(start.x, start.y);
    for (int col = constants::kPlayableLeftCol; col <= constants::kPlayableRightCol; ++col) {
        renderer_.write(kEmptyCell);
        renderer_.sleep(constants::kLineClearAnimationSleepMs);
    }
}

void TetrisView::showGameOver() {
    renderer_.setColor(ConsoleColor::Red);
    printAt(15, 8, "┏━━━━━━━━━━━━━┓");
    printAt(15, 9, "┃**************************┃");
    printAt(15, 10, "┃*        GAME OVER       *┃");
    printAt(15, 11, "┃**************************┃");
    printAt(15, 12, "┗━━━━━━━━━━━━━┛");
    renderer_.flush();
    renderer_.sleep(constants::kGameOverDelayMs);
}

void TetrisView::moveCursorOutOfGameArea() { renderer_.moveCursor(kCursorSafeX, kCursorSafeY); }

void TetrisView::sleep(int milliseconds) { renderer_.sleep(milliseconds); }

void TetrisView::clearScreen() { renderer_.clear(); }

void TetrisView::drawBlockCells(const Tetromino& block, const std::string& cellText) {
    const Position position = block.getPosition();
    for (int row = 0; row < constants::kBlockMatrixSize; ++row) {
        for (int col = 0; col < constants::kBlockMatrixSize; ++col) {
            if (!block.hasCell(row, col) || position.y + row < 0) {
                continue;
            }
            const Position screen = toScreenPosition(position.x + col, position.y + row);
            printAt(screen.x, screen.y, cellText);
        }
    }
}

void TetrisView::printAt(int x, int y, const std::string& text) {
    renderer_.moveCursor(x, y);
    renderer_.write(text);
}

Position TetrisView::toScreenPosition(int boardX, int boardY) const {
    return {(boardX * 2) + boardOffset_.x, boardY + boardOffset_.y};
}

}  // namespace tetris
