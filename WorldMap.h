//
// Created by KunstDerFuge on 2/15/18.
//

#ifndef HEADSPACE_TILEMAP_H
#define HEADSPACE_TILEMAP_H


#include <vector>
#include <map>
#define CHUNK_WIDTH 128

enum terrainType {
    dirt, sand, boulder, gravel, water, ice
};

struct Point {
    int x;
    int y;

    Point(int x, int y);
    std::pair<int, int> toPair();
    float distanceTo(Point& b);
    float squaredDistanceTo(Point& b);
};

struct Tile {
    terrainType terrain;
};

class Chunk {
private:
    Tile tiles[CHUNK_WIDTH][CHUNK_WIDTH];
public:
    Tile getTile(int x, int y);
};

class WorldMap {
private:
    std::map<int, std::map<int, Chunk*>> chunks;
public:
    Tile getTile(Point coord);
    std::pair<int, int> getChunkCoord(Point coord);
    Chunk* getChunk(int x, int y);
    void generateChunk(int x, int y);
    bool chunkExists(int x, int y);
    WorldMap(int width);
    ~WorldMap();
};


#endif //HEADSPACE_TILEMAP_H
