#ifndef CONSOLE_INPUT_H
#define CONSOLE_INPUT_H

#include "IInputProvider.h"

namespace tetris {

class ConsoleInput : public IInputProvider {
public:
    ConsoleInput() = default;
    ~ConsoleInput() override = default;

    bool hasKey() override;
    GameKey readKey() override;
    void waitForAnyKey() override;
};

}  // namespace tetris

#endif  // CONSOLE_INPUT_H
