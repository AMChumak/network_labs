//
// Created by anton on 12/5/24.
//

#include "StepStrategyStd.h"

namespace engine {
    /*!
     * @brief does one step for all snakes
     * @param [in] snakes shared pointer to vector of snakes in field
     */
    void StepStrategyStd::step(const std::shared_ptr<std::vector<Snake>> snakes)
    {
        for (auto snake =  snakes->begin(); snake != snakes->end(); ++snake)
        {
            snake->step();
        }
    }
} // engine