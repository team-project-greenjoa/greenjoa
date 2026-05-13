#include "GameStats.h"

namespace tetris {

void GameStats::reset() {
    level_ = 0;
    score_ = 0;
    linesInCurrentStage_ = 0;
}

int GameStats::getLevel() const { return level_; }

int GameStats::getScore() const { return score_; }

int GameStats::getLinesInCurrentStage() const { return linesInCurrentStage_; }

void GameStats::setLevel(int level) { level_ = level; }

void GameStats::addLines(int lines) { linesInCurrentStage_ += lines; }

void GameStats::addScore(int score) { score_ += score; }

void GameStats::nextLevel() { ++level_; }

void GameStats::resetStageLines() { linesInCurrentStage_ = 0; }

}  // namespace tetris
