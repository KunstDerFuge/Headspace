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
    sf::Texture* texture;
    WorldMap* worldMap;

public:
    explicit Player(Point location);
    void takeDamage(int amount);
    bool addToInventory(Item* item);
    sf::Vector2f getPlayerCenter();
    Point getPlayerLocation();
    bool move(int direction);
    void render(sf::RenderWindow &window);
    void placeInWorldMap(WorldMap* worldMap);
};


#endif //HEADSPACE_PLAYER_H
