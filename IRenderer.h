#ifndef I_RENDERER_H
#define I_RENDERER_H

#include <string>
#include "ConsoleTypes.h"

namespace tetris {

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual void moveCursor(int x, int y) = 0;
    virtual void setColor(ConsoleColor color) = 0;
    virtual void write(const std::string& text) = 0;
    virtual void clear() = 0;
    virtual void flush() = 0;
    virtual void sleep(int milliseconds) = 0;
};

}  // namespace tetris

#endif  // I_RENDERER_H
