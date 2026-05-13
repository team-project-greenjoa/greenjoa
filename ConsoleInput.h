#ifndef CONSOLE_INPUT_H
#define CONSOLE_INPUT_H

#include "IInputProvider.h"

#ifndef _WIN32
#include <termios.h>
#endif

namespace tetris {

class ConsoleInput : public IInputProvider {
public:
    ConsoleInput();
    ~ConsoleInput() override;

    bool hasKey() override;
    GameKey readKey() override;
    void waitForAnyKey() override;

private:
#ifndef _WIN32
    termios originalTerminal_{};
    bool terminalConfigured_ = false;

    void configureTerminal();
    void restoreTerminal();
#endif
};

}  // namespace tetris

#endif  // CONSOLE_INPUT_H
