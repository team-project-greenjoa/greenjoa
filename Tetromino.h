#ifndef TETROMINO_H
#define TETROMINO_H

#include <array>
#include "ConsoleTypes.h"
#include "GameConstants.h"

namespace tetris {

enum class TetrominoShape {
    I = 0,
    O,
    T,
    J,
    L,
    Z,
    S,
};

class Tetromino {
public:
    Tetromino(TetrominoShape shape, int rotation = 0, Position position = {});

    TetrominoShape getShape() const;
    int getRotation() const;
    Position getPosition() const;
    void setPosition(Position position);
    void setRotation(int rotation);
    void moveBy(int deltaX, int deltaY);
    void rotateClockwise();
    bool hasCell(int row, int col) const;
    ConsoleColor getColor() const;

private:
    TetrominoShape shape_;
    int rotation_;
    Position position_;
};

class TetrominoData {
public:
    static bool hasCell(TetrominoShape shape, int rotation, int row, int col);
    static ConsoleColor colorOf(TetrominoShape shape);

private:
    using Matrix = std::array<std::array<int, constants::kBlockMatrixSize>, constants::kBlockMatrixSize>;
    using Rotations = std::array<Matrix, constants::kRotationCount>;
    using ShapeTable = std::array<Rotations, constants::kTetrominoCount>;

    static const ShapeTable& shapes();
};

}  // namespace tetris

#endif  // TETROMINO_H
