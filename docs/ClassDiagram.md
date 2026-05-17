# Tetris OOP Class Diagram

```mermaid
classDiagram
    class TetrisGame {
        -Board board_
        -GameStats stats_
        -StageManager stageManager_
        -RandomBlockGenerator blockGenerator_
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
        +isFilled(int, int) bool
        +isCollision(Tetromino) bool
        +merge(Tetromino) void
        +findFullLines() vector~int~
        +clearLines(vector~int~) void
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
        -int score_
        -int linesInCurrentStage_
        +addLines(int) void
        +addScore(int) void
        +resetStageLines() void
    }

    class StageManager {
        -array~StageConfig~ stages_
        -int currentLevel_
        +setLevel(int) void
        +getLevel() int
        +currentStage() StageConfig
        +levelUp() void
    }

    class StageConfig {
        -int speed_
        -int stickRate_
        -int clearLineGoal_
    }

    class RandomBlockGenerator {
        -mt19937 engine_
        +makeNextShape(StageConfig) TetrominoShape
        +nextScoreBonus(int) int
    }

    class TetrisView {
        -IRenderer renderer_
        +showLogo(IInputProvider) void
        +showBoard(Board, int) void
        +showCurrentBlock(Tetromino) void
        +showNextBlock(TetrominoShape, int) void
        +showGameStats(GameStats, StageManager, bool) void
        +showLineClearAnimation(int) void
    }

    class IRenderer {
        <<interface>>
        +moveCursor(int, int) void
        +setColor(ConsoleColor) void
        +write(string) void
        +clear() void
        +flush() void
        +sleep(int) void
    }

    class ConsoleRenderer

    class IInputProvider {
        <<interface>>
        +hasKey() bool
        +readKey() GameKey
        +waitForAnyKey() void
    }

    class ConsoleInput

    TetrisGame *-- Board
    TetrisGame *-- GameStats
    TetrisGame *-- StageManager
    TetrisGame *-- Tetromino
    TetrisGame o-- RandomBlockGenerator
    TetrisGame o-- TetrisView
    TetrisGame o-- IInputProvider
    TetrisView o-- IRenderer
    ConsoleRenderer ..|> IRenderer
    ConsoleInput ..|> IInputProvider
    StageManager *-- StageConfig
    Tetromino ..> TetrominoData
```

## Design notes for the OOP assignment

- `TetrisGame` controls the overall game flow, while `Board`, `Tetromino`, `GameStats`, and `StageManager` each manage one clear part of the game state.
- Member variables are kept private, and each class exposes only the methods needed by the rest of the program.
- `IRenderer` and `IInputProvider` remain as simple interface examples for inheritance and polymorphism. `ConsoleRenderer` and `ConsoleInput` provide the Windows console implementations.
- `RandomBlockGenerator` is a normal helper class instead of a separate interface, which keeps the project easier to explain at an undergraduate OOP assignment level.
- `Board` exposes `isFilled(row, col)` instead of exposing its full internal grid to the view.
- Full-line handling is split into `findFullLines()` and `clearLines()` so `TetrisGame` can show the line-clear animation before removing lines.
- The project is intentionally Windows-console-only. Platform-specific input and rendering code uses `conio.h`, `Windows.h`, `_kbhit()`, `_getch()`, `SetConsoleCursorPosition()`, and `SetConsoleTextAttribute()` inside `ConsoleInput` and `ConsoleRenderer`.
