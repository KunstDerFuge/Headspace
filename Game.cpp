//
// Created by KunstDerFuge on 2/28/18.
//

#include "Game.h"

void Game::logMessage(std::wstring message, message_type type) {
    console->logMessage(message, type);
}

Game::Game(const sf::RenderWindow& window) {
    world = new World(window);
    console = new Console();
}

void Game::render(sf::RenderWindow &window) {
    getPlayer()->shouldRedrawMap = false;
    window.clear(sf::Color::Black);
    world->renderMap(window);
    console->render(window);
}

Game::~Game() {
    delete world;
    delete console;
}

