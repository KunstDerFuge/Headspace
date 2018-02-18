//
// Created by KunstDerFuge on 1/23/18.
//

#ifndef HEADSPACE_PLAYER_H
#define HEADSPACE_PLAYER_H

#include "Inventory.h"
#include "WorldMap.h"

class Item;

class Player {
private:
    Point location;

public:
    explicit Player(Point location);
    void takeDamage(int amount);
    bool addToInventory(Item* item);
    sf::Vector2f getPlayerCenter();
    Point getPlayerLocation();
};


#endif //HEADSPACE_PLAYER_H
