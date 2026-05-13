#ifndef CONSOLE_RENDERER_H
#define CONSOLE_RENDERER_H

#include "IRenderer.h"

namespace tetris {

class ConsoleRenderer : public IRenderer {
public:
    void moveCursor(int x, int y) override;
    void setColor(ConsoleColor color) override;
    void write(const std::string& text) override;
    void clear() override;
    void flush() override;
    void sleep(int milliseconds) override;
};

}  // namespace tetris

#endif  // CONSOLE_RENDERER_H
