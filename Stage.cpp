#include "Stage.h"

#include <algorithm>

namespace tetris {

StageConfig::StageConfig(int speed, int stickRate, int clearLineGoal)
    : speed_(speed), stickRate_(stickRate), clearLineGoal_(clearLineGoal) {}

int StageConfig::getSpeed() const { return speed_; }

int StageConfig::getStickRate() const { return stickRate_; }

int StageConfig::getClearLineGoal() const { return clearLineGoal_; }

StageRepository::StageRepository()
    : stages_{StageConfig{40, 20, 20}, StageConfig{38, 18, 20}, StageConfig{35, 18, 20},
              StageConfig{30, 17, 20}, StageConfig{25, 16, 20}, StageConfig{20, 14, 20},
              StageConfig{15, 14, 20}, StageConfig{10, 13, 20}, StageConfig{6, 12, 20},
              StageConfig{4, 11, 99999}} {}

const StageConfig& StageRepository::getStage(int level) const {
    const int safeLevel = std::clamp(level, 0, getLastStageIndex());
    return stages_[safeLevel];
}

int StageRepository::getLastStageIndex() const { return static_cast<int>(stages_.size()) - 1; }

}  // namespace tetris
