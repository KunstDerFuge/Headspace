//
// Created by main on 2/28/18.
//

#include "Game.h"

void Game::logMessage(std::string message, message_type type) {
    console->logMessage(message, type);
}

Game::Game() {
    world = new World();
    console = new Console();
}

void Game::render(sf::RenderWindow &window) {
    world->renderMap(window);
    console->render(window);
}

Game::~Game() {
    delete world;
    delete console;
}

