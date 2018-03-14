//
// Created by KunstDerFuge on 1/23/18.
//

#ifndef HEADSPACE_PLAYER_H
#define HEADSPACE_PLAYER_H

#include <SFML/Graphics/VertexArray.hpp>

#include "Inventory.h"
#include "WorldMap.h"
#include "Creature.h"
#include "Utilities.h"

class Item;
class FieldOfView;

struct VisibleMap {
    int width;
    int height;
    sf::Texture* texture;
    Tile** tiles;
    FieldOfView* fov;
    WorldMap* worldMap;
    sf::VertexArray tileMap;
    sf::Vector2f getCenter();
    VisibleMap(FieldOfView* fov, WorldMap* worldMap);
    bool isOnScreen(Point location);
    void updateVisible();
    sf::Vector2f getRenderCoord(Point location);
    int localCoordToIndex(int x, int y);

    void resize();
};

class Player : public Creature {
private:
    sf::Texture* texture;
    sf::Texture* cursorTexture;
    FieldOfView* fov;
    VisibleMap* visibleMap;
    bool examining;
    Point* focus;

public:
    bool shouldRedrawMap;
    Player(Point location, WorldMap* worldMap, const sf::RenderWindow& window);
    void takeDamage(int amount);
    bool addToInventory(Item* item);
    sf::Vector2f getPlayerCenter();
    bool move(direction dir);

    bool canSee(long x, long y);
    void updateFOV();
    void updateVisible();
    void resizeFOV(sf::RenderWindow& window);
    void resizeVisible();
    void renderMap(sf::RenderWindow& window);
    void renderCursors(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    void placeInWorldMap(WorldMap* worldMap);
    Point getFocus();
    VisibleMap* getVisibleMap();
    void examine();
    void cancelAll();
    bool isExamining() {
        return examining;
    }
    void moveFocus(direction dir);

    void renderMonsters(sf::RenderWindow &window);
};


#endif //HEADSPACE_PLAYER_H
