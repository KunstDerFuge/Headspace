//
// Created by KunstDerFuge on 1/23/18.
//

#include "Player.h"

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

Player::Player(Point location) : location(location) {
}

sf::Vector2f Player::getPlayerCenter() {
    return {location.x, location.y};
}

Point Player::getPlayerLocation() {
    return location;
}
