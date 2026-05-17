#include "ConsoleInput.h"

#include <conio.h>

namespace tetris {
namespace {
constexpr int kWindowsExtendedKeyPrefix = 0xE0;
constexpr int kWindowsExtendedKeyPrefixAlt = 0;
constexpr int kWindowsLeftKey = 0x4B;
constexpr int kWindowsRightKey = 0x4D;
constexpr int kWindowsUpKey = 0x48;
constexpr int kWindowsDownKey = 0x50;
constexpr int kSpaceKey = 32;
}  // namespace

bool ConsoleInput::hasKey() { return _kbhit() != 0; }

GameKey ConsoleInput::readKey() {
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
}

void ConsoleInput::waitForAnyKey() { (void)_getch(); }

}  // namespace tetris
