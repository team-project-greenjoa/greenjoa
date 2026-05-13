#ifndef STAGE_H
#define STAGE_H

#include <array>
#include "GameConstants.h"

namespace tetris {

class StageConfig {
public:
    StageConfig(int speed, int stickRate, int clearLineGoal);

    int getSpeed() const;
    int getStickRate() const;
    int getClearLineGoal() const;

private:
    int speed_;
    int stickRate_;
    int clearLineGoal_;
};

class StageRepository {
public:
    StageRepository();

    const StageConfig& getStage(int level) const;
    int getLastStageIndex() const;

private:
    std::array<StageConfig, constants::kStageCount> stages_;
};

}  // namespace tetris

#endif  // STAGE_H
