//
// Created by KunstDerFuge on 2/15/18.
//

#ifndef HEADSPACE_TILEMAP_H
#define HEADSPACE_TILEMAP_H


#include <vector>
#include <map>

enum terrainType {
    dirt, sand, boulder, gravel, water, ice
};

struct Point {
    int x;
    int y;

    Point(int x, int y);
    float distanceTo(Point& b);
    float squaredDistanceTo(Point& b);
};

struct Tile {
    terrainType terrain;
};

class Chunk {
private:
    std::map<int, std::map<int, Tile>> tiles;
public:
    Tile getTile(int x, int y);
};

class WorldMap {
private:
    std::map<int, std::map<int, Chunk>> chunks;
public:
    Tile getTile(Point coord);
    Point toChunkCoord(Point coord);
};


#endif //HEADSPACE_TILEMAP_H
