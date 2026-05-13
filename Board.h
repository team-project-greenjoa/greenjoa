#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "GameConstants.h"
#include "Tetromino.h"

namespace tetris {

class Board {
public:
    using Grid = std::array<std::array<int, constants::kBoardCols>, constants::kBoardRows>;

    Board();

    void reset();
    bool hasFixedBlock(int row, int col) const;
    bool isCollision(const Tetromino& tetromino) const;
    void merge(const Tetromino& tetromino);
    int clearFullLines();
    const Grid& getGrid() const;

private:
    bool isWallOrFloor(int row, int col) const;
    bool isInsideGrid(int row, int col) const;

    Grid grid_{};
};

}  // namespace tetris

#endif  // BOARD_H
