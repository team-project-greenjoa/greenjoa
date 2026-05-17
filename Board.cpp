#include "Board.h"

namespace tetris {

Board::Board() { reset(); }

void Board::reset() {
    for (int row = 0; row < constants::kBoardRows; ++row) {
        for (int col = 0; col < constants::kBoardCols; ++col) {
            grid_[row][col] = isWallOrFloor(row, col) ? 1 : 0;
        }
    }
}

bool Board::isFilled(int row, int col) const {
    if (!isInsideGrid(row, col)) {
        return true;
    }
    return grid_[row][col] == 1;
}

bool Board::isCollision(const Tetromino& tetromino) const {
    const Position position = tetromino.getPosition();
    for (int row = 0; row < constants::kBlockMatrixSize; ++row) {
        for (int col = 0; col < constants::kBlockMatrixSize; ++col) {
            if (!tetromino.hasCell(row, col)) {
                continue;
            }

            const int boardRow = position.y + row;
            const int boardCol = position.x + col;
            if (boardRow < 0) {
                if (boardCol <= constants::kLeftWallCol || boardCol >= constants::kRightWallCol) {
                    return true;
                }
                continue;
            }
            if (isFilled(boardRow, boardCol)) {
                return true;
            }
        }
    }
    return false;
}

void Board::merge(const Tetromino& tetromino) {
    const Position position = tetromino.getPosition();
    for (int row = 0; row < constants::kBlockMatrixSize; ++row) {
        for (int col = 0; col < constants::kBlockMatrixSize; ++col) {
            if (!tetromino.hasCell(row, col)) {
                continue;
            }
            const int boardRow = position.y + row;
            const int boardCol = position.x + col;
            if (isInsideGrid(boardRow, boardCol)) {
                grid_[boardRow][boardCol] = 1;
            }
        }
    }
}

std::vector<int> Board::findFullLines() const {
    std::vector<int> fullLines;
    for (int row = 0; row < constants::kVisibleRows; ++row) {
        bool full = true;
        for (int col = constants::kPlayableLeftCol; col <= constants::kPlayableRightCol; ++col) {
            if (grid_[row][col] == 0) {
                full = false;
                break;
            }
        }
        if (full) {
            fullLines.push_back(row);
        }
    }
    return fullLines;
}

void Board::clearLines(const std::vector<int>& rows) {
    for (int row : rows) {
        clearSingleLine(row);
    }
}

bool Board::isWallOrFloor(int row, int col) const {
    return col == constants::kLeftWallCol || col == constants::kRightWallCol || row == constants::kBottomRow;
}

bool Board::isInsideGrid(int row, int col) const {
    return row >= 0 && row < constants::kBoardRows && col >= 0 && col < constants::kBoardCols;
}

void Board::clearSingleLine(int row) {
    for (int pullRow = row; pullRow > 0; --pullRow) {
        for (int col = constants::kPlayableLeftCol; col <= constants::kPlayableRightCol; ++col) {
            grid_[pullRow][col] = grid_[pullRow - 1][col];
        }
    }
    for (int col = constants::kPlayableLeftCol; col <= constants::kPlayableRightCol; ++col) {
        grid_[0][col] = 0;
    }
}

}  // namespace tetris
