#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

namespace tetris::constants {
constexpr int kBoardRows = 21;
constexpr int kVisibleRows = 20;
constexpr int kBoardCols = 14;
constexpr int kLeftWallCol = 0;
constexpr int kRightWallCol = kBoardCols - 1;
constexpr int kBottomRow = kBoardRows - 1;
constexpr int kPlayableLeftCol = 1;
constexpr int kPlayableRightCol = kBoardCols - 2;
constexpr int kBlockMatrixSize = 4;
constexpr int kTetrominoCount = 7;
constexpr int kRotationCount = 4;
constexpr int kDefaultBoardOffsetX = 5;
constexpr int kDefaultBoardOffsetY = 1;
constexpr int kStartBlockX = 5;
constexpr int kStartBlockY = -4;
constexpr int kPreviewBoxX = 33;
constexpr int kPreviewBoxY = 1;
constexpr int kPreviewBlockX = 15;
constexpr int kPreviewBlockY = 1;
constexpr int kStageCount = 10;
constexpr int kSelectableMinLevel = 1;
constexpr int kSelectableMaxLevel = 8;
constexpr int kScoreBase = 100;
constexpr int kScorePerLevel = 10;
constexpr int kScoreRandomBonusExclusive = 10;
constexpr int kGameLoopSleepMs = 15;
constexpr int kLogoSleepMs = 100;
constexpr int kLogoAnimationSleepMs = 30;
constexpr int kLineClearAnimationSleepMs = 10;
constexpr int kGameOverDelayMs = 1000;
constexpr int kInputBufferIgnoreSize = 1024;
}  // namespace tetris::constants

#endif  // GAME_CONSTANTS_H
