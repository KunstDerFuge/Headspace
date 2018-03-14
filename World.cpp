//
// Created by KunstDerFuge on 2/10/18.
//

#include <iostream>
#include "World.h"
#include "WorldMap.h"
#include "Player.h"

using namespace std;

World::World(const sf::RenderWindow& window) {
    overworld = new WorldMap();
    player = new Player(Point(0, 0), overworld, window);
    player->placeInWorldMap(overworld);
    creatures.push_back(new Creature(Point(1, 1), overworld));
    creatures.push_back(creatures[0]->generateRandom(SIZE_LARGE, overworld));
    for (int i = 0; i < 50000; ++i)
        creatures.push_back(creatures[0]->generateRandom(SIZE_COLOSSAL, overworld));
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
