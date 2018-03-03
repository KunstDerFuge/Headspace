//
// Created by KunstDerFuge on 2/10/18.
//

#include <iostream>
#include "World.h"
#include "WorldMap.h"
#include "Player.h"

using namespace std;

World::World() {
    overworld = new WorldMap();
    player = new Player(Point(0, 0));
    player->placeInWorldMap(overworld);
}

void World::renderMap(sf::RenderWindow& window) {
    overworld->render(window, player);
}

World::~World() {
    cerr << "World destructor" << std::endl;
    delete player;
    delete overworld;
}

WorldMap *World::getOverworld() {
    return overworld;
}
