#include "ConsoleRenderer.h"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <Windows.h>

namespace tetris {

ConsoleRenderer::ConsoleRenderer() { setCursorVisible(false); }

// Windows console only: restore the user's cursor when the renderer goes out of scope.
ConsoleRenderer::~ConsoleRenderer() { setCursorVisible(true); }

void ConsoleRenderer::moveCursor(int x, int y) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = static_cast<SHORT>(x);
    pos.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition(console, pos);
}

void ConsoleRenderer::setColor(ConsoleColor color) {
    static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, static_cast<WORD>(color));
}

void ConsoleRenderer::write(const std::string& text) { std::cout << text; }

void ConsoleRenderer::clear() { std::system("cls"); }

void ConsoleRenderer::flush() { std::cout.flush(); }

void ConsoleRenderer::sleep(int milliseconds) { std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds)); }

void ConsoleRenderer::setCursorVisible(bool visible) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo{};
    if (GetConsoleCursorInfo(console, &cursorInfo) != 0) {
        cursorInfo.bVisible = visible ? TRUE : FALSE;
        SetConsoleCursorInfo(console, &cursorInfo);
    }
}

}  // namespace tetris
