#include "ConsoleInput.h"

#include <iostream>

#ifdef _WIN32
#include <conio.h>
#else
#include <fcntl.h>
#include <sys/select.h>
#include <unistd.h>
#endif

namespace tetris {
namespace {
constexpr int kWindowsExtendedKeyPrefix = 0xE0;
constexpr int kWindowsExtendedKeyPrefixAlt = 0;
constexpr int kWindowsLeftKey = 0x4B;
constexpr int kWindowsRightKey = 0x4D;
constexpr int kWindowsUpKey = 0x48;
constexpr int kWindowsDownKey = 0x50;
constexpr int kSpaceKey = 32;
constexpr char kEscapeKey = '\033';
constexpr char kAnsiBracket = '[';
constexpr char kAnsiLeftKey = 'D';
constexpr char kAnsiRightKey = 'C';
constexpr char kAnsiUpKey = 'A';
constexpr char kAnsiDownKey = 'B';
}  // namespace

ConsoleInput::ConsoleInput() = default;

ConsoleInput::~ConsoleInput() {
#ifndef _WIN32
    restoreTerminal();
#endif
}

bool ConsoleInput::hasKey() {
#ifdef _WIN32
    return _kbhit() != 0;
#else
    if (!terminalConfigured_) {
        configureTerminal();
    }
    timeval timeout{};
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    return select(STDIN_FILENO + 1, &readfds, nullptr, nullptr, &timeout) > 0;
#endif
}

GameKey ConsoleInput::readKey() {
#ifdef _WIN32
    const int first = _getch();
    if (first == kSpaceKey) {
        return GameKey::Drop;
    }
    if (first == kWindowsExtendedKeyPrefix || first == kWindowsExtendedKeyPrefixAlt) {
        const int second = _getch();
        switch (second) {
            case kWindowsLeftKey:
                return GameKey::Left;
            case kWindowsRightKey:
                return GameKey::Right;
            case kWindowsUpKey:
                return GameKey::Rotate;
            case kWindowsDownKey:
                return GameKey::Down;
            default:
                return GameKey::Any;
        }
    }
    return GameKey::Any;
#else
    if (!terminalConfigured_) {
        configureTerminal();
    }
    char first = 0;
    if (::read(STDIN_FILENO, &first, 1) <= 0) {
        return GameKey::None;
    }
    if (first == kSpaceKey) {
        return GameKey::Drop;
    }
    if (first == kEscapeKey) {
        char second = 0;
        char third = 0;
        if (::read(STDIN_FILENO, &second, 1) <= 0 || second != kAnsiBracket ||
            ::read(STDIN_FILENO, &third, 1) <= 0) {
            return GameKey::Any;
        }
        switch (third) {
            case kAnsiLeftKey:
                return GameKey::Left;
            case kAnsiRightKey:
                return GameKey::Right;
            case kAnsiUpKey:
                return GameKey::Rotate;
            case kAnsiDownKey:
                return GameKey::Down;
            default:
                return GameKey::Any;
        }
    }
    return GameKey::Any;
#endif
}

void ConsoleInput::waitForAnyKey() {
#ifdef _WIN32
    _getch();
#else
    if (!terminalConfigured_) {
        char ignored = 0;
        std::cin.get(ignored);
        return;
    }
    while (!hasKey()) {
        usleep(10000);
    }
    (void)readKey();
#endif
}

#ifndef _WIN32
void ConsoleInput::configureTerminal() {
    if (tcgetattr(STDIN_FILENO, &originalTerminal_) != 0) {
        return;
    }
    termios raw = originalTerminal_;
    raw.c_lflag &= static_cast<unsigned int>(~(ICANON | ECHO));
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) == 0) {
        terminalConfigured_ = true;
    }
}

void ConsoleInput::restoreTerminal() {
    if (terminalConfigured_) {
        tcsetattr(STDIN_FILENO, TCSANOW, &originalTerminal_);
    }
}
#endif

}  // namespace tetris
