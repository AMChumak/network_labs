//
// Created by anton on 12/5/24.
//

#include "StepStrategyStd.h"

namespace ganeEngine {
    void StepStrategyStd::step(std::shared_ptr<std::vector<gameEngine::Snake>> snakes)
    {
        for(auto snake: *snakes)
        {
            snake.step();
        }
    }
} // ganeEngine