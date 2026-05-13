#ifndef I_INPUT_PROVIDER_H
#define I_INPUT_PROVIDER_H

#include "ConsoleTypes.h"

namespace tetris {

class IInputProvider {
public:
    virtual ~IInputProvider() = default;

    virtual bool hasKey() = 0;
    virtual GameKey readKey() = 0;
    virtual void waitForAnyKey() = 0;
};

}  // namespace tetris

#endif  // I_INPUT_PROVIDER_H
