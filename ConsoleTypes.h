#ifndef CONSOLE_TYPES_H
#define CONSOLE_TYPES_H

namespace tetris {

enum class ConsoleColor {
    Black = 0,
    DarkBlue,
    DarkGreen,
    DarkSkyBlue,
    DarkRed,
    DarkViolet,
    DarkYellow,
    Gray,
    DarkGray,
    Blue,
    Green,
    SkyBlue,
    Red,
    Violet,
    Yellow,
    White,
};

enum class GameKey {
    None,
    Left,
    Right,
    Rotate,
    Down,
    Drop,
    Any,
};

struct Position {
    int x = 0;
    int y = 0;
};

}  // namespace tetris

#endif  // CONSOLE_TYPES_H
