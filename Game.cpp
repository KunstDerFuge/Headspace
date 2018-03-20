//
// Created by KunstDerFuge on 2/28/18.
//

#include <SFML/Graphics/RenderTexture.hpp>
#include <vector>
#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shader.hpp>
#include "Game.h"
#include "Creature.h"

using namespace std;

void Game::logMessage(std::wstring message, message_type type) {
    console->logMessage(message, type);
}

Game::Game(const sf::RenderWindow& window) {
    auto mapRenderWidth = static_cast<unsigned int>(window.getSize().x * (1.f - CONSOLE_WIDTH));
    mapWindow.create(mapRenderWidth, window.getSize().y);
    world = new World(mapWindow);
    console = new Console();
}

void Game::render(sf::RenderWindow &window) {
    window.clear(sf::Color::Black);
    mapWindow.clear(sf::Color::Black);
    //world->renderMap(window);
    world->getPlayer()->renderMap(mapWindow);
    world->getPlayer()->render(mapWindow);
    world->getPlayer()->renderMonsters(mapWindow);
    world->getPlayer()->renderCursors(mapWindow);
    sf::Sprite mapWindowSprite;
    sf::Vector2f windowSize(window.getSize().x, window.getSize().y);
    sf::Texture mapWindowTexture = mapWindow.getTexture();
    mapWindowSprite.setTexture(mapWindowTexture);
    mapWindowSprite.setScale(1.f, -1.f);
    mapWindowSprite.setPosition(0, windowSize.y);

    // MAP-LEVEL SHADERS GO HERE
//    sf::Shader crt;
//    crt.loadFromFile(shadersPath() + "/shader-laferriere.frag", sf::Shader::Fragment);
//    crt.setUniform("u_texture", mapWindowTexture);
//    crt.setUniform("sourceSize", sf::Vector2f(mapWindow.getSize().x/1.f, mapWindow.getSize().y/1.f));

    window.draw(mapWindowSprite);
    console->render(window);
}

Game::~Game() {
    delete world;
    delete console;
}

bool Game::movePlayer(direction dir) {
    // Check if player is examining or moving
    if (getPlayer()->isExamining()) {
        getPlayer()->moveFocus(dir);
        return true;
    }
    // Check for monsters in this direction
    Point movingTo = getPlayer()->getAdjacentPoint(dir);
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

sf::RenderTexture &Game::getMapWindow() {
    return mapWindow;
}

void Game::resizeMapWindow(sf::RenderWindow &window) {
    auto mapRenderWidth = static_cast<unsigned int>(window.getSize().x * (1.f - CONSOLE_WIDTH));
    mapWindow.create(mapRenderWidth, window.getSize().y);
}

