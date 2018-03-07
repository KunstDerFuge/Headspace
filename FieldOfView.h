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
    std::vector<Cell> squares;
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
    /* number of allocated angle pairs */
    int allocated;
public:
    bool isVisible(long x, long y);
    void markAsVisible(long x, long y);
    void update(Creature* creature);
    void invalidate(int tileWidth, const sf::RenderWindow& window);
    FieldOfView(Creature* creature, const sf::RenderWindow& window, int tileWidth, WorldMap* worldMap);
};


#endif //HEADSPACE_FIELDOFVIEW_H
