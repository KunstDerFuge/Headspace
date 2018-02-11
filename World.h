//
// Created by KunstDerFuge on 2/10/18.
//

#ifndef HEADSPACE_WORLD_H
#define HEADSPACE_WORLD_H

#include <vector>

class Creature;
class Player;

class World {
private:
    std::vector<Creature*> creatures;
    Player* player;
public:
};

#endif //HEADSPACE_WORLD_H
