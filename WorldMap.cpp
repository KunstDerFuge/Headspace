//
// Created by KunstDerFuge on 2/15/18.
//

#include <cmath>
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include "WorldMap.h"
#include "Player.h"

using namespace std;

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

float Point::squaredDistanceTo(Point& b) {
    float dx = b.x - this->x;
    float dy = b.y - this->y;
    return (dx*dx) + (dy*dy);
}

float Point::distanceTo(Point& b) {
    return float(sqrt(squaredDistanceTo(b)));
}

std::pair<int, int> Point::toPair() {
    return std::make_pair(x, y);
}

Tile WorldMap::getTile(Point coord) {
    int tileX = coord.x % CHUNK_WIDTH;
    int tileY = coord.y % CHUNK_WIDTH;
    std::pair<int, int> chunkCoord = getChunkCoord(coord);
    return chunks[chunkCoord.first][chunkCoord.second]->getTile(tileX, tileY);
}

std::pair<int, int> WorldMap::getChunkCoord(Point coord) {
    if (coord.x < 0) {
        coord.x += 1;
        coord.x /= CHUNK_WIDTH;
        coord.x -= 1;
    }
    else {
        coord.x /= CHUNK_WIDTH;
    }
    if (coord.y < 0) {
        coord.y += 1;
        coord.y /= CHUNK_WIDTH;
        coord.y -= 1;
    }
    else {
        coord.y /= CHUNK_WIDTH;
    }
    return std::make_pair(coord.x, coord.y);
}

Chunk* WorldMap::getChunk(int x, int y) {
    return chunks[x][y];
}

void WorldMap::generateChunk(int x, int y) {
    if (chunkExists(x, y))
        cerr << "Generating chunk where one already exists: (" << x << ", " << y << ")" << endl;
    //cerr << "Generating chunk at (" << x << ", " << y << ")..." << endl;
    chunks[x][y] = new Chunk();
}

bool WorldMap::chunkExists(int x, int y) {
    auto column = chunks.find(x);
    if (column == chunks.end())
        return false;
    auto chunk = column->second.find(y);
    return (chunk != column->second.end());
}

WorldMap::~WorldMap() {
    for (auto const &ent1 : chunks)
        for (auto const &ent2 : ent1.second) {
            delete ent2.second;
            cerr << "Deleted a chunk!" << endl;
        }
    cerr << "Deleted worldMap!" << endl;
}

WorldMap::WorldMap(int width) {
    int offset = width / 2;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < width; ++y) {
            generateChunk(offset+x, offset+y);
        }
    }
}

void WorldMap::render(sf::RenderWindow& window, Player* player) {

    Point playerLocation = player->getPlayerLocation();
    sf::View playerView(player->getPlayerCenter(), sf::Vector2f(300, 300));
    auto width = int(playerView.getSize().x);
    auto height = int(playerView.getSize().y);
    int upperLeftBoundX = playerLocation.x - (width / 2);
    int upperLeftBoundY = playerLocation.y - (height / 2);
    for (int x = upperLeftBoundX; x < upperLeftBoundX + width; ++x) {
        for (int y = upperLeftBoundY; y < upperLeftBoundY + height; ++y) {
            sf::RectangleShape tile;
            tile.setPosition(upperLeftBoundX + x, upperLeftBoundY + y);
            tile.setSize(sf::Vector2f(10.f, 1.f));
            tile.setFillColor(sf::Color::Green);
            window.draw(tile);
        }
    }
}

Tile Chunk::getTile(int x, int y) {
    return tiles[x][y];
}
