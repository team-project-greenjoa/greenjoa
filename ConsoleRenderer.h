#ifndef CONSOLE_RENDERER_H
#define CONSOLE_RENDERER_H

#include "IRenderer.h"

namespace tetris {

class ConsoleRenderer : public IRenderer {
public:
    // Hide the terminal caret during gameplay so it does not flicker over moving blocks.
    ConsoleRenderer();
    ~ConsoleRenderer() override;

    void moveCursor(int x, int y) override;
    void setColor(ConsoleColor color) override;
    void write(const std::string& text) override;
    void clear() override;
    void flush() override;
    void sleep(int milliseconds) override;

private:
    void setCursorVisible(bool visible);
};

}  // namespace tetris

#endif  // CONSOLE_RENDERER_H
