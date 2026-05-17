#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <vector>
#include "GameConstants.h"
#include "Tetromino.h"

namespace tetris {

class Board {
public:
    Board();

    void reset();
    bool isFilled(int row, int col) const;
    bool isCollision(const Tetromino& tetromino) const;
    void merge(const Tetromino& tetromino);
    std::vector<int> findFullLines() const;
    void clearLines(const std::vector<int>& rows);

private:
    using Grid = std::array<std::array<int, constants::kBoardCols>, constants::kBoardRows>;

    bool isWallOrFloor(int row, int col) const;
    bool isInsideGrid(int row, int col) const;
    void clearSingleLine(int row);

    Grid grid_{};
};

}  // namespace tetris

#endif  // BOARD_H
