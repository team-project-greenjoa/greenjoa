#ifndef I_BLOCK_GENERATOR_H
#define I_BLOCK_GENERATOR_H

#include "Stage.h"
#include "Tetromino.h"

namespace tetris {

class IBlockGenerator {
public:
    virtual ~IBlockGenerator() = default;

    virtual TetrominoShape makeNextShape(const StageConfig& stage) = 0;
    virtual int nextScoreBonus(int exclusiveUpperBound) = 0;
};

}  // namespace tetris

#endif  // I_BLOCK_GENERATOR_H
