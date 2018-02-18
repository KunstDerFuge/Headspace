//
// Created by KunstDerFuge on 2/10/18.
//

#include <iostream>
#include "World.h"
#include "WorldMap.h"
#include "Player.h"

World::World(int width) {
    worldMap = new WorldMap(width);
    player = new Player(Point(0, 0));
}

void World::renderMap(sf::RenderWindow& window) {
    worldMap->render(window, player);
}

World::~World() {
    std::cerr << "World destructor" << std::endl;
    delete player;
    delete worldMap;
}
