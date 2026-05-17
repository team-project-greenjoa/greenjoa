#include "RandomBlockGenerator.h"

#include <chrono>

namespace tetris {

RandomBlockGenerator::RandomBlockGenerator()
    : engine_(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())) {}

TetrominoShape RandomBlockGenerator::makeNextShape(const StageConfig& stage) {
    std::uniform_int_distribution<int> percent(0, 99);
    if (percent(engine_) < stage.getStickRate()) {
        return TetrominoShape::I;
    }

    std::uniform_int_distribution<int> shape(1, constants::kTetrominoCount - 1);
    return static_cast<TetrominoShape>(shape(engine_));
}

int RandomBlockGenerator::nextScoreBonus(int exclusiveUpperBound) {
    if (exclusiveUpperBound <= 0) {
        return 0;
    }
    std::uniform_int_distribution<int> bonus(0, exclusiveUpperBound - 1);
    return bonus(engine_);
}

}  // namespace tetris
