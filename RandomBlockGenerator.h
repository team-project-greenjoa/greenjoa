#ifndef RANDOM_BLOCK_GENERATOR_H
#define RANDOM_BLOCK_GENERATOR_H

#include <random>
#include "IBlockGenerator.h"

namespace tetris {

class RandomBlockGenerator : public IBlockGenerator {
public:
    RandomBlockGenerator();

    TetrominoShape makeNextShape(const StageConfig& stage) override;
    int nextScoreBonus(int exclusiveUpperBound) override;

private:
    std::mt19937 engine_;
};

}  // namespace tetris

#endif  // RANDOM_BLOCK_GENERATOR_H
