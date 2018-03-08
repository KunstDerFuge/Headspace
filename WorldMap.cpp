//
// Created by KunstDerFuge on 2/15/18.
//

#include <cmath>
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "WorldMap.h"
#include "Player.h"
#include "Utilities.h"

using namespace std;

Point::Point(long x, long y) {
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

std::pair<long, long> Point::toPair() {
    return std::make_pair(x, y);
}

Tile* WorldMap::getTile(Point coord) {
    int tileX = mod(coord.x,  CHUNK_WIDTH);
    int tileY = mod(coord.y,  CHUNK_WIDTH);
    std::pair<long, long> chunkCoord = getChunkCoord(coord);
    if (!chunkExists(chunkCoord.first, chunkCoord.second)) {
        generateChunk(chunkCoord.first, chunkCoord.second, this);
    }
    return chunks[chunkCoord.first][chunkCoord.second]->getTile(tileX, tileY);
}

std::pair<long, long> WorldMap::getChunkCoord(Point coord) {
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

Chunk* WorldMap::getChunk(long x, long y) {
    return chunks[x][y];
}

void WorldMap::generateChunk(long x, long y, WorldMap* worldMap) {
    if (chunkExists(x, y))
        cerr << "Generating chunk where one already exists: (" << x << ", " << y << ")" << endl;
    cerr << "Generating chunk at (" << x << ", " << y << ")..." << endl;
    chunks[x][y] = new Chunk(worldMap);
}

bool WorldMap::chunkExists(long x, long y) {
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
    cerr << "Deleted overworld!" << endl;
}

WorldMap::WorldMap() {
    int width = 1;
    int offset = width / 2;

    uniqueTiles.push_back(new Tile(dirt, 8, 8));
    auto dirt = uniqueTiles[0];
    dirt->texture = new sf::Texture;
    dirt->texture->loadFromFile(graphicsPath() + "/dirt_seamless_shrink.jpg");

    uniqueTiles.push_back(new Tile(ice, 8, 8));
    auto ice = uniqueTiles[1];
    ice->texture = new sf::Texture;
    ice->texture->loadFromFile(graphicsPath() + "/snow.jpg");

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < width; ++y) {
            cerr << "WorldMap constructor: generating chunk" << endl;
            generateChunk(offset+x, offset+y, this);
        }
    }
}

void WorldMap::render(sf::RenderWindow& window, Player* player) {
    player->updateFOV();
    auto mapViewportWidth = float(1.f - CONSOLE_WIDTH);
    auto playerLocation = player->getPlayerLocation();
    auto windowSize = window.getSize();
    auto mapRenderSize = sf::Vector2f(windowSize.x * mapViewportWidth, windowSize.y);
    auto viewWidthInTiles = int(mapRenderSize.x / TILE_WIDTH);
    auto viewHeightInTiles = int(mapRenderSize.y / TILE_WIDTH);
    sf::View playerView(player->getPlayerCenter(), tileToRenderCoord(viewWidthInTiles, viewHeightInTiles));
    auto renderWidthInTiles = viewWidthInTiles + 2;
    auto renderHeightInTiles = viewHeightInTiles + 2;
    long upperLeftTileX = playerLocation.x - renderWidthInTiles / 2;
    long upperLeftTileY = playerLocation.y - renderHeightInTiles / 2;
    playerView.setViewport(sf::FloatRect(0.f, 0.f, mapViewportWidth, 1.f));
    playerView.setSize(mapRenderSize);
    window.setView(playerView);

    // Render map
    for (long x = upperLeftTileX; x < upperLeftTileX + renderWidthInTiles; ++x) {
        for (long y = upperLeftTileY; y < upperLeftTileY + renderHeightInTiles; ++y) {
            auto tile = getTile(Point(x, y));
            getTile(Point(x, y))->render(x, y, window, player->canSee(x, y));
        }
    }

    // Render player
    player->render(window);

}

Tile* WorldMap::getUniqueTile(int tileNumber) {
    return uniqueTiles[tileNumber];
}

bool WorldMap::isWalkable(Point coord) {
    return (getTile(coord)->terrain != ice);
}

bool WorldMap::isOpaque(Point coord) {
    return !isWalkable(coord);
}

Tile* Chunk::getTile(long x, long y) {
    return tiles[x][y];
}

Chunk::Chunk(WorldMap* worldMap) {
    for (auto& column : tiles) {
        for (auto& tile : column) {
            if (randomBool(0.99)) {
                tile = worldMap->getUniqueTile(0);
            }
            else {
                tile = worldMap->getUniqueTile(1);
            }
        }
    }
}

void Tile::render(long x, long y, sf::RenderWindow& window, bool inFOV) {
    sf::RectangleShape tile;
    tile.setPosition(tileToRenderCoord(x, y));
    tile.setSize(sf::Vector2f(TILE_WIDTH, TILE_WIDTH));
    if (!inFOV) {
        return;
//        tile.setFillColor(sf::Color::Black);
    } else {
        auto textureXCoord = int(mod(x, this->textureWidthTiles) * 32);
        auto textureYCoord = int(mod(y, this->textureHeightTiles) * 32);
        tile.setTexture(this->texture);
        tile.setTextureRect(sf::IntRect(textureXCoord, textureYCoord, 32, 32));
    }
    window.draw(tile);
}

Tile::Tile(terrainType terrain, int textureWidth, int textureHeight) {
    this->terrain = terrain;
    this->textureWidthTiles = textureWidth;
    this->textureHeightTiles = textureHeight;
}
