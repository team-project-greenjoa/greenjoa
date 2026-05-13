#include "Tetromino.h"

#include <array>

namespace tetris {
namespace {
int normalizeRotation(int rotation) {
    constexpr int rotationCount = constants::kRotationCount;
    return ((rotation % rotationCount) + rotationCount) % rotationCount;
}
}  // namespace

Tetromino::Tetromino(TetrominoShape shape, int rotation, Position position)
    : shape_(shape), rotation_(normalizeRotation(rotation)), position_(position) {}

TetrominoShape Tetromino::getShape() const { return shape_; }

int Tetromino::getRotation() const { return rotation_; }

Position Tetromino::getPosition() const { return position_; }

void Tetromino::setPosition(Position position) { position_ = position; }

void Tetromino::setRotation(int rotation) { rotation_ = normalizeRotation(rotation); }

void Tetromino::moveBy(int deltaX, int deltaY) {
    position_.x += deltaX;
    position_.y += deltaY;
}

void Tetromino::rotateClockwise() { setRotation(rotation_ + 1); }

bool Tetromino::hasCell(int row, int col) const {
    return TetrominoData::hasCell(shape_, rotation_, row, col);
}

ConsoleColor Tetromino::getColor() const { return TetrominoData::colorOf(shape_); }

bool TetrominoData::hasCell(TetrominoShape shape, int rotation, int row, int col) {
    if (row < 0 || row >= constants::kBlockMatrixSize || col < 0 || col >= constants::kBlockMatrixSize) {
        return false;
    }
    return shapes()[static_cast<int>(shape)][normalizeRotation(rotation)][row][col] == 1;
}

ConsoleColor TetrominoData::colorOf(TetrominoShape shape) {
    switch (shape) {
        case TetrominoShape::I:
            return ConsoleColor::Red;
        case TetrominoShape::O:
            return ConsoleColor::Blue;
        case TetrominoShape::T:
            return ConsoleColor::SkyBlue;
        case TetrominoShape::J:
            return ConsoleColor::White;
        case TetrominoShape::L:
            return ConsoleColor::Yellow;
        case TetrominoShape::Z:
            return ConsoleColor::Violet;
        case TetrominoShape::S:
            return ConsoleColor::Green;
    }
    return ConsoleColor::Gray;
}

const TetrominoData::ShapeTable& TetrominoData::shapes() {
    static const ShapeTable table = {{
        // I
        Rotations{{
            Matrix{{{{1, 0, 0, 0}}, {{1, 0, 0, 0}}, {{1, 0, 0, 0}}, {{1, 0, 0, 0}}}},
            Matrix{{{{1, 1, 1, 1}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{1, 0, 0, 0}}, {{1, 0, 0, 0}}, {{1, 0, 0, 0}}, {{1, 0, 0, 0}}}},
            Matrix{{{{1, 1, 1, 1}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}},
        }},
        // O
        Rotations{{
            Matrix{{{{1, 1, 0, 0}}, {{1, 1, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{1, 1, 0, 0}}, {{1, 1, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{1, 1, 0, 0}}, {{1, 1, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{1, 1, 0, 0}}, {{1, 1, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}},
        }},
        // T
        Rotations{{
            Matrix{{{{0, 1, 0, 0}}, {{1, 1, 0, 0}}, {{0, 1, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{1, 1, 1, 0}}, {{0, 1, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{1, 0, 0, 0}}, {{1, 1, 0, 0}}, {{1, 0, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{0, 1, 0, 0}}, {{1, 1, 1, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}},
        }},
        // J
        Rotations{{
            Matrix{{{{1, 1, 0, 0}}, {{0, 1, 0, 0}}, {{0, 1, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{1, 1, 1, 0}}, {{1, 0, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{1, 0, 0, 0}}, {{1, 0, 0, 0}}, {{1, 1, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{0, 0, 1, 0}}, {{1, 1, 1, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}},
        }},
        // L
        Rotations{{
            Matrix{{{{1, 1, 0, 0}}, {{1, 0, 0, 0}}, {{1, 0, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{1, 0, 0, 0}}, {{1, 1, 1, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{0, 1, 0, 0}}, {{0, 1, 0, 0}}, {{1, 1, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{1, 1, 1, 0}}, {{0, 0, 1, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}},
        }},
        // Z
        Rotations{{
            Matrix{{{{1, 1, 0, 0}}, {{0, 1, 1, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{0, 1, 0, 0}}, {{1, 1, 0, 0}}, {{1, 0, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{1, 1, 0, 0}}, {{0, 1, 1, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{0, 1, 0, 0}}, {{1, 1, 0, 0}}, {{1, 0, 0, 0}}, {{0, 0, 0, 0}}}},
        }},
        // S
        Rotations{{
            Matrix{{{{0, 1, 1, 0}}, {{1, 1, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{1, 0, 0, 0}}, {{1, 1, 0, 0}}, {{0, 1, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{0, 1, 1, 0}}, {{1, 1, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}},
            Matrix{{{{1, 0, 0, 0}}, {{1, 1, 0, 0}}, {{0, 1, 0, 0}}, {{0, 0, 0, 0}}}},
        }},
    }};
    return table;
}

}  // namespace tetris
