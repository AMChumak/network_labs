#ifndef PLAYER_H
#define PLAYER_H
#include <string>

#include "proto/snakes.pb.h"

namespace engine {

class Player {
public:
    Player (int i_id, const std::string& i_name, int i_score = 0);

    GamePlayer generate_state() const;
    int get_player_id() const;
    std::string get_name();


public:
    int score;
private:
    int id;
    std::string name;
};

} // engine

#endif //PLAYER_H
