//
// Created by KunstDerFuge on 1/23/18.
//

#ifndef HEADSPACE_PLAYER_H
#define HEADSPACE_PLAYER_H

#include "Inventory.h"
#include "WorldMap.h"
#include "Creature.h"
#include "FieldOfView.h"

class Item;

class Player : public Creature {
private:
    sf::Texture* texture;
    FieldOfView* fov;

public:
    Player(Point location, WorldMap* worldMap, const sf::RenderWindow& window);
    void takeDamage(int amount);
    bool addToInventory(Item* item);
    sf::Vector2f getPlayerCenter();
    Point getPlayerLocation();
    bool move(int direction);
    bool canSee(long x, long y);
    void updateFOV();
    void render(sf::RenderWindow &window);
    void placeInWorldMap(WorldMap* worldMap);
};


#endif //HEADSPACE_PLAYER_H
