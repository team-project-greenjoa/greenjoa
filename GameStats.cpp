#include "GameStats.h"

namespace tetris {

void GameStats::reset() {
    score_ = 0;
    linesInCurrentStage_ = 0;
}

int GameStats::getScore() const { return score_; }

int GameStats::getLinesInCurrentStage() const { return linesInCurrentStage_; }

void GameStats::addLines(int lines) { linesInCurrentStage_ += lines; }

void GameStats::addScore(int score) { score_ += score; }

void GameStats::resetStageLines() { linesInCurrentStage_ = 0; }

}  // namespace tetris
