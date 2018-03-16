//
// Created by KunstDerFuge on 2/15/18.
//

#ifndef HEADSPACE_TILEMAP_H
#define HEADSPACE_TILEMAP_H


#include <vector>
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Utilities.h"

class Player;
class WorldMap;
class Creature;

const int NUM_TERRAIN_TYPES = 6;

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
    std::vector<Creature*> creatures;
public:
    Tile* getTile(Point coord);
    std::pair<long, long> getChunkCoord(Point coord);
    Chunk* getChunk(long x, long y);
    void generateChunk(long x, long y, WorldMap* worldMap);
    bool chunkExists(long x, long y);
    void render(sf::RenderTexture& mapWindow, Player* player);
    Tile* getUniqueTile(int tileNumber);
    bool isWalkable(Point coord);
    bool isWalkable(Player* player, direction dir);
    bool isOpaque(Point coord);
    void addCreature(Creature* creature);
    std::vector<Creature*>* getCreatures();
    explicit WorldMap();
    ~WorldMap();
};


#endif //HEADSPACE_TILEMAP_H
