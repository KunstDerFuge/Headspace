//
// Created by KunstDerFuge on 2/15/18.
//

#include <cmath>
#include <iostream>
#include "WorldMap.h"

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
    for (int i = 0; i < width; i++) {
        generateChunk(i, 0);
        generateChunk(0, i);
    }
}

Tile Chunk::getTile(int x, int y) {
    return tiles[x][y];
}
