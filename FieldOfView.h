//
// Created by main on 3/4/18.
//

#ifndef HEADSPACE_FIELDOFVIEW_H
#define HEADSPACE_FIELDOFVIEW_H


#include <vector>
#include "Creature.h"

class FieldOfView {
private:
    std::vector<bool> squares;
    void castRay(Point from, Point to);
    long mapCoordToIndex(long x, long y);
    WorldMap* worldMap;
    int width;
    int height;
    long top;
    long left;
public:
    bool isVisible(long x, long y);
    void markAsVisible(long x, long y);
    void update(Creature *creature);
    void invalidate(int tileWidth, const sf::RenderWindow& window);
    FieldOfView(Creature* creature, const sf::RenderWindow& window, int tileWidth, WorldMap* worldMap);
};


#endif //HEADSPACE_FIELDOFVIEW_H
