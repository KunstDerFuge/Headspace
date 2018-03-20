//
// Created by KunstDerFuge on 1/23/18.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <SFML/Graphics/Shader.hpp>
#include "Player.h"
#include "FieldOfView.h"

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

Player::Player(Point location, WorldMap* worldMap, const sf::RenderTexture& mapWindow) : Creature(location, worldMap) {
    shouldRedrawMap = true;
    texture = new sf::Texture;
    texture->loadFromFile(graphicsPath() + "/sample.png");
    cursorTexture = new sf::Texture;
    cursorTexture->loadFromFile(graphicsPath() + "/cursor.png");
    fov = new FieldOfView(this, mapWindow, TILE_WIDTH, worldMap);
    visibleMap = new VisibleMap(fov, worldMap);
    focus = nullptr;
    examining = false;
}

sf::Vector2f Player::getPlayerCenter() {
    return {location.x*TILE_WIDTH + (TILE_WIDTH/2), location.y*TILE_WIDTH + (TILE_WIDTH/2)};
}

void Player::render(sf::RenderTexture& window) {
    sf::RectangleShape tile;
    sf::Vector2f mapCenter = visibleMap->getCenter();
    float halfTileWidth = TILE_WIDTH / 2.f;
    tile.setPosition(sf::Vector2f(mapCenter.x - halfTileWidth, mapCenter.y - halfTileWidth));
    tile.setSize(sf::Vector2f(TILE_WIDTH, TILE_WIDTH));
    tile.setTexture(texture);
//    window.draw(tile);
}

bool Player::move(direction dir) {
    shouldRedrawMap = true;
    if (!worldMap->isWalkable(this, dir))
        return false;

    switch(dir) {
        case west:
            --location.x;
            break;
        case north:
            --location.y;
            break;
        case south:
            ++location.y;
            break;
        case east:
            ++location.x;
            break;
        case northwest:
            --location.x;
            --location.y;
            break;
        case northeast:
            ++location.x;
            --location.y;
            break;
        case southwest:
            --location.x;
            ++location.y;
            break;
        case southeast:
            ++location.x;
            ++location.y;
            break;
        default:
        cerr << "Tried to move in nonexistent direction: " << dir << endl;
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
    cout << "Updating FOV" << endl;
    fov->update();
}

void Player::resizeFOV(sf::RenderTexture& mapWindow) {
    fov->invalidate(TILE_WIDTH, mapWindow);
}

void Player::updateVisible() {
    visibleMap->updateVisible();
}

void Player::resizeVisible() {
    visibleMap->resize();
}

void Player::renderMap(sf::RenderTexture &mapWindow) {
    if (shouldRedrawMap) {
        updateFOV();
        updateVisible();
    }
    shouldRedrawMap = false;
    sf::View playerView;
    auto visibleMapCenter = visibleMap->getCenter();
    auto mapSize = mapWindow.getSize();
    playerView.setSize(mapSize.x, mapSize.y);
    playerView.setCenter(visibleMapCenter);
    mapWindow.setView(playerView);
    mapWindow.draw(visibleMap->tileMap, visibleMap->texture);
}

void Player::renderMonsters(sf::RenderTexture& mapWindow) {
    auto creatures = *worldMap->getCreatures();
    for (auto &creature : creatures) {
        if (!visibleMap->isOnScreen(creature->getLocation()))
            continue;
        if (fov->isVisible(creature->getLocation())) {
            creature->render(texture, visibleMap, mapWindow);
        }
    }
}

void Player::examine() {
    if (examining)
        return;
    examining = true;
    focus = new Point(location);
}

void Player::cancelAll() {
    examining = false;
    delete focus;
    focus = nullptr;
    shouldRedrawMap = true;
}

Point Player::getFocus() {
    if (focus == nullptr)
        return location;
    return *focus;
}

void Player::moveFocus(direction dir) {
    if (focus == nullptr)
        focus = new Point(location);
    auto newFocus = getAdjacentLocation(*focus, dir);
    focus->x = newFocus.x;
    focus->y = newFocus.y;
    updateFOV();
    updateVisible();
}

VisibleMap *Player::getVisibleMap() {
    return visibleMap;
}

void Player::renderCursors(sf::RenderTexture& mapWindow) {
    if (examining) {
        sf::RectangleShape cursor;
        cursor.setPosition(visibleMap->getRenderCoord(getFocus()));
        cursor.setSize(sf::Vector2f(TILE_WIDTH, TILE_WIDTH));
        cursor.setTexture(cursorTexture);
        mapWindow.draw(cursor);
    }
}

VisibleMap::VisibleMap(FieldOfView* fov, WorldMap* worldMap) {
    this->width = fov->getWidth();
    this->height = fov->getHeight();
    this->worldMap = worldMap;
    this->fov = fov;
    tiles = new Tile*[width * height];
    tileMap.setPrimitiveType(sf::Quads);
    tileMap.resize(static_cast<size_t>(width * height * 4));
    texture = new sf::Texture;
    if (!texture->loadFromFile(graphicsPath() + "/dirt_seamless_shrink.jpg")) {
        cerr << "Could not load texture!" << endl;
    } else {
        cout << "Loaded texture" << endl;
    }
}

void VisibleMap::updateVisible() {
    long left = fov->getLeft();
    long top = fov->getTop();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            tiles[localCoordToIndex(x, y)] = worldMap->getTile(Point(x + left, y + top));
            tileMap.setPrimitiveType(sf::Quads);
            tileMap.resize(static_cast<size_t>(width * height * 4));
            float tileTop = y * TILE_WIDTH;
            float tileLeft = x * TILE_WIDTH;
            int quadIndex = localCoordToIndex(x, y) * 4;
            sf::Vertex* quad = &tileMap[quadIndex];
            if (!fov->isVisible(left + x, top + y)) {
                quad[0].color = sf::Color::Blue;
                quad[1].color = sf::Color::Blue;
                quad[2].color = sf::Color::Blue;
                quad[3].color = sf::Color::Blue;
            } else {
                quad[0].color = sf::Color::White;
                quad[1].color = sf::Color::White;
                quad[2].color = sf::Color::White;
                quad[3].color = sf::Color::White;
            }
            quad[0].position = sf::Vector2f(tileLeft, tileTop);
            quad[1].position = sf::Vector2f(tileLeft + TILE_WIDTH, tileTop);
            quad[2].position = sf::Vector2f(tileLeft + TILE_WIDTH, tileTop + TILE_WIDTH);
            quad[3].position = sf::Vector2f(tileLeft, tileTop + TILE_WIDTH);
            auto texCoordX = mod((left + x) * 32, 256);
            auto texCoordY = mod((top + y) * 32, 256);
            quad[0].texCoords = sf::Vector2f(texCoordX, texCoordY);
            quad[1].texCoords = sf::Vector2f(texCoordX + TILE_WIDTH, texCoordY);
            quad[2].texCoords = sf::Vector2f(texCoordX + TILE_WIDTH, texCoordY + TILE_WIDTH);
            quad[3].texCoords = sf::Vector2f(texCoordX, texCoordY + TILE_WIDTH);
//            quad[0].color = sf::Color::Magenta;
//            quad[1].color = sf::Color::Green;
//            quad[2].color = sf::Color::Black;
//            quad[3].color = sf::Color::White;
//            tileMap.append(sf::Vertex(sf::Vector2f(tileLeft, tileTop)));
//            tileMap.append(sf::Vertex(sf::Vector2f(tileLeft + TILE_WIDTH, tileTop)));
//            tileMap.append(sf::Vertex(sf::Vector2f(tileLeft + TILE_WIDTH, tileTop + TILE_WIDTH)));
//            tileMap.append(sf::Vertex(sf::Vector2f(tileLeft, tileTop + TILE_WIDTH)));
        }
    }
}

int VisibleMap::localCoordToIndex(int x, int y) {
    return (y * width) + x;
}

sf::Vector2f VisibleMap::getCenter() {
    auto bounds = tileMap.getBounds();
    auto centerX = bounds.left + (bounds.width / 2.f);
    auto centerY = bounds.top + (bounds.height / 2.f);
    return sf::Vector2f(centerX, centerY);
}

void VisibleMap::resize() {
    width = fov->getWidth();
    height = fov->getHeight();
    tiles = new Tile*[width * height];
    tileMap.resize(static_cast<size_t>(width * height * 4));
}

sf::Vector2f VisibleMap::getRenderCoord(Point location) {
    long left = fov->getLeft();
    long top = fov->getTop();
    if (!isOnScreen(location)) {
        return {-10000, -10000};
    }
    float widthPerTile = tileMap.getBounds().width / this->width;
    float heightPerTile = tileMap.getBounds().height / this->height;
    return {(location.x - left) * widthPerTile, (location.y - top) * heightPerTile};
}

bool VisibleMap::isOnScreen(Point location) {
    long left = fov->getLeft();
    long top = fov->getTop();
    return !(location.x < left || location.x > left + width || location.y < top || location.y > top + height);
}
