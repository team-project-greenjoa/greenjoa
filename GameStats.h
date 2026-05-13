#ifndef GAME_STATS_H
#define GAME_STATS_H

namespace tetris {

class GameStats {
public:
    void reset();
    int getLevel() const;
    int getScore() const;
    int getLinesInCurrentStage() const;
    void setLevel(int level);
    void addLines(int lines);
    void addScore(int score);
    void nextLevel();
    void resetStageLines();

private:
    int level_ = 0;
    int score_ = 0;
    int linesInCurrentStage_ = 0;
};

}  // namespace tetris

#endif  // GAME_STATS_H
