#ifndef RANDOM_BLOCK_GENERATOR_H
#define RANDOM_BLOCK_GENERATOR_H

#include <random>
#include "Stage.h"
#include "Tetromino.h"

namespace tetris {

class RandomBlockGenerator {
public:
    RandomBlockGenerator();

    TetrominoShape makeNextShape(const StageConfig& stage);
    int nextScoreBonus(int exclusiveUpperBound);

private:
    std::mt19937 engine_;
};

}  // namespace tetris

#endif  // RANDOM_BLOCK_GENERATOR_H
