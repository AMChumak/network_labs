//
// Created by anton on 1/19/25.
//

#ifndef PLAYERSLISTOBSERVER_H
#define PLAYERSLISTOBSERVER_H

class PlayersListObserver
{
public:
    virtual ~PlayersListObserver() = default;
    virtual void on_player_delete(int player_id)=0;
};

#endif //PLAYERSLISTOBSERVER_H
