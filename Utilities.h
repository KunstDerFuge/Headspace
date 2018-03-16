//
// Created by KunstDerFuge on 1/26/18.
//

#ifndef HEADSPACE_UTILITIES_H
#define HEADSPACE_UTILITIES_H

#include <vector>
#include <string>
#include <SFML/System.hpp>
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>

#define CHUNK_WIDTH 64  // Width and height of a chunk in tiles
#define TILE_WIDTH 32  // Width and height of a tile in pixels
#define CONSOLE_WIDTH 0.2  // Width of the console as a fraction of the window width

enum direction {
    north, south, east, west, northwest, northeast, southwest, southeast
};

enum terrainType {
    dirt, sand, boulder, gravel, water, ice
};

class WorldMap;

struct Point {
    long x;
    long y;

    Point(long x, long y);
    std::pair<long, long> toPair();
    float distanceTo(Point& b);
    float squaredDistanceTo(Point& b);
    bool operator== (const Point& other);
};

struct Tile {
    terrainType terrain;
    sf::Texture* texture;
    int textureWidthTiles;
    int textureHeightTiles;
    void render(long x, long y, sf::RenderTexture& mapWindow, bool inFOV=true);
    explicit Tile(terrainType terrain, int textureWidth=1, int textureHeight=1);
};

int randomChoiceOfN(int n);
int randomFromXToY(int x, int y);
float randomFloatZeroToN(float n);
float randomSampleNormal(float, float);
float randomSampleNormal(float mean, float dev, float min, float max);
int randomChoiceFromWeights(std::initializer_list<int>);
bool randomBool(float chance=0.5);

template<typename t>
t randomChoiceFromVector(std::vector<t> vector);

void toSentenceCase(std::string& in);
void toLowercase(std::string& in);
std::string toPossessive(std::string in);
std::string toOrdinal(int in);
void concatenateWord(std::string& sentence, std::string word);
std::string concatenateWordToCopy(std::string sentence, std::string word);
std::string namePosition(int position, int numberOfPositions, bool useLeftRight);
sf::Vector2f tileToRenderCoord(float x, float y);
long mod(long k, long n);
const std::string assetsPath();
const std::string graphicsPath();
const std::string fontsPath();
const std::string shadersPath();
Point getAdjacentLocation(Point loc, direction dir);

#endif //HEADSPACE_UTILITIES_H
