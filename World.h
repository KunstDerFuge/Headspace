//
// Created by KunstDerFuge on 2/10/18.
//

#ifndef HEADSPACE_WORLD_H
#define HEADSPACE_WORLD_H

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Player.h"

class Creature;
class Player;
class WorldMap;
class Item;

class World {
private:
    std::vector<Creature*> creatures;
    std::vector<Item*> items;
    Player* player;
    WorldMap* overworld;
public:
    explicit World(const sf::RenderWindow& window);
    ~World();
    void renderMap(sf::RenderWindow& window);
    WorldMap* getOverworld();
    Player* getPlayer() {
        return player;
    }
};

#endif //HEADSPACE_WORLD_H
