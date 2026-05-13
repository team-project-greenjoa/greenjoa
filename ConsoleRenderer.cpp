#include "ConsoleRenderer.h"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#endif

namespace tetris {

void ConsoleRenderer::moveCursor(int x, int y) {
#ifdef _WIN32
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = static_cast<SHORT>(x);
    pos.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition(console, pos);
#else
    std::cout << "\033[" << (y + 1) << ';' << (x + 1) << 'H';
#endif
}

void ConsoleRenderer::setColor(ConsoleColor color) {
#ifdef _WIN32
    static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, static_cast<WORD>(color));
#else
    switch (color) {
        case ConsoleColor::Black:
            std::cout << "\033[30m";
            break;
        case ConsoleColor::DarkRed:
        case ConsoleColor::Red:
            std::cout << "\033[31m";
            break;
        case ConsoleColor::DarkGreen:
        case ConsoleColor::Green:
            std::cout << "\033[32m";
            break;
        case ConsoleColor::DarkYellow:
        case ConsoleColor::Yellow:
            std::cout << "\033[33m";
            break;
        case ConsoleColor::DarkBlue:
        case ConsoleColor::Blue:
            std::cout << "\033[34m";
            break;
        case ConsoleColor::DarkViolet:
        case ConsoleColor::Violet:
            std::cout << "\033[35m";
            break;
        case ConsoleColor::DarkSkyBlue:
        case ConsoleColor::SkyBlue:
            std::cout << "\033[36m";
            break;
        case ConsoleColor::DarkGray:
        case ConsoleColor::Gray:
        case ConsoleColor::White:
            std::cout << "\033[37m";
            break;
    }
#endif
}

void ConsoleRenderer::write(const std::string& text) { std::cout << text; }

void ConsoleRenderer::clear() {
#ifdef _WIN32
    std::system("cls");
#else
    std::cout << "\033[2J\033[H";
#endif
}

void ConsoleRenderer::flush() { std::cout.flush(); }

void ConsoleRenderer::sleep(int milliseconds) { std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds)); }

}  // namespace tetris
