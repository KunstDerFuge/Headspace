//
// Created by KunstDerFuge on 1/23/18.
//

#ifndef HEADSPACE_PLAYER_H
#define HEADSPACE_PLAYER_H

#include "Inventory.h"

class Item;

class Player {
private:

public:
    Player();
    void takeDamage(int amount);
    bool addToInventory(Item* item);
};


#endif //HEADSPACE_PLAYER_H
