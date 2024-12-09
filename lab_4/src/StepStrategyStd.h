//
// Created by anton on 12/5/24.
//

#ifndef STEPSTRATEGYSTD_H
#define STEPSTRATEGYSTD_H
#include "MoveStrategies.h"

namespace ganeEngine {

class StepStrategyStd : public gameEngine::StepStrategyI {
public:
    void step(std::shared_ptr<std::vector<gameEngine::Snake>> snakes) override;
};

} // ganeEngine

#endif //STEPSTRATEGYSTD_H
