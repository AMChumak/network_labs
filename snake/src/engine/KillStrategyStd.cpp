//
// Created by anton on 12/6/24.
//

#include "KillStrategyStd.h"

namespace engine {
    void KillStrategyStd::kill(std::shared_ptr<std::vector<Snake>> snakes)
    {
        //FIND INTERSECTS SNAKES
        std::vector<long> del_idxes;
        for (auto it = snakes->begin(), end_it = snakes->end(); it != end_it; ++it)
        {
            for (auto another_it = snakes->begin(); another_it != end_it; ++another_it)
            {
                if (another_it != it && another_it->intersect(it->get_head_coord()))
                {
                    del_idxes.push_back(it - snakes->begin());
                }
            }
        }

        //KILL SNAKES
        int correction = 0;
        for (const long &idx : del_idxes)
        {
            snakes->erase(snakes->begin() + idx - (correction++));
        }
    }
} // engine