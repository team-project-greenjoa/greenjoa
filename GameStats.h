#ifndef GAME_STATS_H
#define GAME_STATS_H

namespace tetris {

class GameStats {
public:
    void reset();
    int getScore() const;
    int getLinesInCurrentStage() const;
    void addLines(int lines);
    void addScore(int score);
    void resetStageLines();

private:
    int score_ = 0;
    int linesInCurrentStage_ = 0;
};

}  // namespace tetris

#endif  // GAME_STATS_H
