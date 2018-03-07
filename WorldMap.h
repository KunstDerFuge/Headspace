//
// Created by KunstDerFuge on 2/15/18.
//

#ifndef HEADSPACE_TILEMAP_H
#define HEADSPACE_TILEMAP_H


#include <vector>
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

#define CHUNK_WIDTH 64  // Width and height of a chunk in tiles
#define TILE_WIDTH 32  // Width and height of a tile in pixels
#define CONSOLE_WIDTH 0.2  // Width of the console as a fraction of the window width

class Player;
class WorldMap;

enum terrainType {
    dirt, sand, boulder, gravel, water, ice
};

const int NUM_TERRAIN_TYPES = 6;

struct Point {
    long x;
    long y;

    Point(long x, long y);
    std::pair<long, long> toPair();
    float distanceTo(Point& b);
    float squaredDistanceTo(Point& b);
};

struct Tile {
    terrainType terrain;
    sf::Texture* texture;
    int textureWidthTiles;
    int textureHeightTiles;
    void render(long x, long y, sf::RenderWindow& window, bool inFOV=true);
    explicit Tile(terrainType terrain, int textureWidth=1, int textureHeight=1);
};

class Chunk {
private:
    Tile* tiles[CHUNK_WIDTH][CHUNK_WIDTH];
public:
    Tile* getTile(long x, long y);
    explicit Chunk(WorldMap* worldMap);
};

class WorldMap {
private:
    std::map<long, std::map<long, Chunk*>> chunks;
    std::vector<sf::Texture*> uniqueTextures;
    std::vector<Tile*> uniqueTiles;
public:
    Tile* getTile(Point coord);
    std::pair<long, long> getChunkCoord(Point coord);
    Chunk* getChunk(long x, long y);
    void generateChunk(long x, long y, WorldMap* worldMap);
    bool chunkExists(long x, long y);
    void render(sf::RenderWindow& window, Player* player);
    Tile* getUniqueTile(int tileNumber);
    bool isWalkable(Point coord);
    bool isOpaque(Point coord);
    explicit WorldMap();
    ~WorldMap();
};


#endif //HEADSPACE_TILEMAP_H
