# Tetris OOP Class Diagram

```mermaid
classDiagram
    class TetrisGame {
        -Board board_
        -GameStats stats_
        -StageRepository stageRepository_
        -Tetromino currentBlock_
        -TetrominoShape nextShape_
        -bool gameOver_
        +run() void
        -moveCurrentBlockDown() MoveResult
        -lockCurrentBlockAndSpawnNext() void
    }

    class Board {
        -Grid grid_
        +reset() void
        +isCollision(Tetromino) bool
        +merge(Tetromino) void
        +clearFullLines() int
    }

    class Tetromino {
        -TetrominoShape shape_
        -int rotation_
        -Position position_
        +moveBy(int, int) void
        +rotateClockwise() void
        +hasCell(int, int) bool
    }

    class TetrominoData {
        +hasCell(TetrominoShape, int, int, int) bool
        +colorOf(TetrominoShape) ConsoleColor
    }

    class GameStats {
        -int level_
        -int score_
        -int linesInCurrentStage_
        +addLines(int) void
        +addScore(int) void
        +nextLevel() void
    }

    class StageRepository {
        -array~StageConfig~ stages_
        +getStage(int) StageConfig
    }

    class StageConfig {
        -int speed_
        -int stickRate_
        -int clearLineGoal_
    }

    class TetrisView {
        -IRenderer renderer_
        +showBoard(Board, int) void
        +showCurrentBlock(Tetromino) void
        +showNextBlock(TetrominoShape, int) void
        +showGameStats(GameStats, StageConfig, bool) void
    }

    class IRenderer {
        <<interface>>
        +moveCursor(int, int) void
        +setColor(ConsoleColor) void
        +write(string) void
        +clear() void
    }

    class ConsoleRenderer
    class IInputProvider {
        <<interface>>
        +hasKey() bool
        +readKey() GameKey
        +waitForAnyKey() void
    }

    class ConsoleInput
    class IBlockGenerator {
        <<interface>>
        +makeNextShape(StageConfig) TetrominoShape
        +nextScoreBonus(int) int
    }

    class RandomBlockGenerator

    TetrisGame *-- Board
    TetrisGame *-- GameStats
    TetrisGame *-- StageRepository
    TetrisGame *-- Tetromino
    TetrisGame o-- TetrisView
    TetrisGame o-- IInputProvider
    TetrisGame o-- IBlockGenerator
    TetrisView o-- IRenderer
    ConsoleRenderer ..|> IRenderer
    ConsoleInput ..|> IInputProvider
    RandomBlockGenerator ..|> IBlockGenerator
    StageRepository *-- StageConfig
    Tetromino ..> TetrominoData
```

## Reuse-focused design notes

- `IRenderer`, `IInputProvider`, and `IBlockGenerator` are pure abstract interfaces, so console rendering, input, and block generation can be replaced in another project without changing `TetrisGame`.
- `Board`, `Tetromino`, `GameStats`, and `StageRepository` each own a single responsibility and keep data private behind focused public methods.
- `TetrisGame` composes reusable components instead of depending on global variables.
- Gameplay constants are centralized in `GameConstants.h` to remove hard-coded magic numbers from the core logic.
