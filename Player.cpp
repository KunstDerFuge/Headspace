//
// Created by KunstDerFuge on 1/23/18.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include "Player.h"
#include "Utilities.h"

using namespace std;

//void Player::takeDamage(int amount) {
//    health -= amount;
//    if (health < 0) {
//        health = 0;
//    }
//}
//
//bool Player::addToInventory(Item *item) {
//    if (inventory->getTotalWeight() >= carryCapacity) {
//        return false;
//    }
//    inventory->addItem(item);
//    return true;
//}
//
//Player::Player() {
//    health = 100;
//    inventory = new Inventory();
//}

Player::Player(Point location, WorldMap* worldMap, const sf::RenderWindow& window) : Creature(location, worldMap) {
    shouldRedrawMap = true;
    texture = new sf::Texture;
    texture->loadFromFile(graphicsPath() + "/sample.png");
    fov = new FieldOfView(this, window, TILE_WIDTH, worldMap);
}

sf::Vector2f Player::getPlayerCenter() {
    return {location.x*TILE_WIDTH + (TILE_WIDTH/2), location.y*TILE_WIDTH + (TILE_WIDTH/2)};
}

Point Player::getPlayerLocation() {
    return location;
}

void Player::render(sf::RenderWindow& window) {
    sf::RectangleShape tile;
    tile.setPosition(tileToRenderCoord(location.x, location.y));
    tile.setSize(sf::Vector2f(TILE_WIDTH, TILE_WIDTH));
    tile.setTexture(texture);
    window.draw(tile);
}

bool Player::move(int direction) {
    shouldRedrawMap = true;
    switch(direction) {
        case 0:
            if (worldMap->isWalkable(Point(location.x-1, location.y))) {
                --location.x;
            } else {
                return false;
            }
            break;
        case 1:
            if (worldMap->isWalkable(Point(location.x, location.y+1))) {
                ++location.y;
            } else {
                return false;
            }
            break;
        case 2:
            if (worldMap->isWalkable(Point(location.x, location.y-1))) {
                --location.y;
            } else {
                return false;
            }
            break;
        case 3:
            if (worldMap->isWalkable(Point(location.x+1, location.y))) {
                ++location.x;
            } else {
                return false;
            }
            break;
        default:
        cerr << "Tried to move in nonexistent direction: " << direction << endl;
        return false;
    }
    return true;
}

void Player::placeInWorldMap(WorldMap* worldMap) {
    this->worldMap = worldMap;
}

bool Player::canSee(long x, long y) {
    return fov->isVisible(x, y);
}

void Player::updateFOV() {
    fov->update();
}

void Player::invalidateFOV(sf::RenderWindow& window) {
    fov->invalidate(TILE_WIDTH, window);
}
