//
// Created by KunstDerFuge on 2/28/18.
//

#include <SFML/Graphics/RenderTexture.hpp>
#include <vector>
#include <iostream>
#include "Game.h"
#include "Creature.h"

using namespace std;

void Game::logMessage(std::wstring message, message_type type) {
    console->logMessage(message, type);
}

Game::Game(const sf::RenderWindow& window) {
    world = new World(window);
    console = new Console();
}

void Game::render(sf::RenderWindow &window) {
    window.clear(sf::Color::Black);
    //world->renderMap(window);
    world->getPlayer()->renderMap(window);
    world->getPlayer()->render(window);
    world->getPlayer()->renderMonsters(window);
    console->render(window);
}

Game::~Game() {
    delete world;
    delete console;
}

bool Game::movePlayer(direction dir) {
    // Check for monsters in this direction
    Point movingTo = getPlayer()->getAdjacentLocation(dir);
    WorldMap* worldMap = getPlayer()->getWorldMap();
    auto creaturesHere = getCreaturesAt(movingTo, worldMap);
    if (!creaturesHere.empty()) {
        cout << "You strike it with the back of your hand!" << endl;
        return false;
    }
    return getPlayer()->move(dir);
}

std::vector<Creature*> Game::getCreaturesAt(Point location, WorldMap* worldMap) {
    auto creatures = *worldMap->getCreatures();
    vector<Creature*> creaturesHere;
    for (auto& creature : creatures) {
        if (creature->getLocation() == location)
            creaturesHere.push_back(creature);
    }
    return creaturesHere;
}

