//
// Created by anton on 12/5/24.
//

#ifndef STEPSTRATEGYSTD_H
#define STEPSTRATEGYSTD_H
#include "MoveStrategies.h"

namespace engine {

class StepStrategyStd : public StepStrategyI {
public:
    void step(std::shared_ptr<std::vector<Snake>> snakes) override;
};

} // engine

#endif //STEPSTRATEGYSTD_H
