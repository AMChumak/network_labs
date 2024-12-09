//
// Created by anton on 12/6/24.
//

#include "KillStrategyStd.h"

namespace gameEngine {
    void KillStrategyStd::kill(std::shared_ptr<std::vector<Snake>> snakes)
    {
        //FIND INTERSECTS SNAKES
        std::vector<long> delIdxs;
        for (auto it = snakes->begin(), endIt = snakes->end(); it != endIt; ++it)
        {
            for (auto anotherIt = snakes->begin(); it != endIt; ++it)
            {
                if (anotherIt != it && anotherIt->intersect(it->getHeadCoord()))
                {
                    delIdxs.push_back(it - snakes->begin());
                }
            }
        }

        //KILL SNAKES
        int correction = 0;
        for (long idx : delIdxs)
        {
            snakes->erase(snakes->begin() + idx - (correction++));
        }
    }
} // gameEngine