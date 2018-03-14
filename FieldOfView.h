//
// Created by KunstDerFuge on 3/4/18.
//

#ifndef HEADSPACE_FIELDOFVIEW_H
#define HEADSPACE_FIELDOFVIEW_H


#include <vector>
#include "Creature.h"
#include "include/libtcod.hpp"

struct Cell {
    bool visible;
    bool transparent;
};

class FieldOfView {
private:
    Creature* creature;
    std::vector<Cell> cells;
    void castRay(Point from, Point to);
    long mapCoordToIndex(long x, long y);
    WorldMap* worldMap;
    int width;
    int height;
    long top;
    long left;
    void computeQuadrant(int player_x, int player_y, int dx, int dy);/* angle ranges */
    double* start_angle;
    double* end_angle;
    int getViewWidthTiles(int resolutionX, int tileWidth);
    int getViewHeightTiles(int resolutionY, int tileWidth);
    /* number of allocated angle pairs */
    int allocated;
public:
    bool isVisible(long x, long y);
    bool isVisible(Point location);
    void markAsVisible(long x, long y);
    void update();
    void invalidate(int tileWidth, const sf::RenderWindow& window);
    FieldOfView(Creature* creature, const sf::RenderWindow& window, int tileWidth, WorldMap* worldMap);
    int getWidth();
    int getHeight();
    long getTop();
    long getLeft();
};


#endif //HEADSPACE_FIELDOFVIEW_H
