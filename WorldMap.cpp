//
// Created by KunstDerFuge on 2/15/18.
//

#include <tgmath.h>
#include "WorldMap.h"

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

float Point::squaredDistanceTo(Point& b) {
    float dx = b.x - this->x;
    float dy = b.y - this->y;
    return (dx * dx) + (dy * dy);
}

float Point::distanceTo(Point& b) {
    return sqrt(squaredDistanceTo(b));
}

Tile WorldMap::getTile(Point coord) {
    int tileX = coord.x % 128;
    int tileY = coord.y % 128;
    return chunks[coord.x][coord.y].getTile(tileX, tileY);
}

Point WorldMap::toChunkCoord(Point coord) {
    if (coord.x < 0) {
        coord.x += 1;
        coord.x /= 128;
        coord.x -= 1;
    }
    else {
        coord.x /= 128;
    }
    if (coord.y < 0) {
        coord.y += 1;
        coord.y /= 128;
        coord.y -= 1;
    }
    else {
        coord.y /= 128;
    }
    return coord;
}

Tile Chunk::getTile(int x, int y) {
    return tiles[x][y];
}
