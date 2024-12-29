//
// Created by anton on 12/5/24.
//

#include <vector>

#include "FoodDistributor.h"
#include "Snake.h"
#ifndef MOVESTRATEGIES_H

namespace gameEngine
{
    class StepStrategyI
    {
    public:
        virtual ~StepStrategyI() = default;
        virtual void step(std::shared_ptr<std::vector<Snake>>snakes)=0;
    };

    class EatStrategyI
    {
    public:
        virtual ~EatStrategyI() = default;
        virtual void eat(std::shared_ptr<std::vector<Snake>>snakes, std::shared_ptr<FoodDistributor> foodDistr)=0;
    };

    class KillStrategyI
    {
    public:
        virtual ~KillStrategyI() = default;
        virtual void kill(std::shared_ptr<std::vector<Snake>>snakes)=0;
    };

    class FindPlaceStrategyI
    {
    public:
        virtual ~FindPlaceStrategyI() = default;
        virtual CoordDirectionPair findPlace(std::shared_ptr<std::vector<Snake>> snakes, std::shared_ptr<FoodDistributor> foodDistr, std::shared_ptr<Field> field)=0;
    };

    class BornStrategyI
    {
    public:
        virtual ~BornStrategyI() = default;
        virtual bool born(const int &ownerId, std::shared_ptr<std::vector<Snake>>snakes, std::shared_ptr<FoodDistributor> foodDistr, std::shared_ptr<Field> field,
                          std::shared_ptr<FindPlaceStrategyI> findPlaceStrategy)=0;
    };


}

#define MOVESTRATEGIES_H

#endif //MOVESTRATEGIES_H
