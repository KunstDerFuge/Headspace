//
// Created by KunstDerFuge on 3/4/18.
// C++ adaptation of Mingos' Restrictive Precise Angle Shadowcasting V1.1 from libtcod.
//

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "FieldOfView.h"

using namespace std;

#define MAX(a,b) ((a)<(b)?(b):(a))
#define MIN(a,b) ((a)>(b)?(b):(a))

bool FieldOfView::isVisible(long x, long y) {
    return squares[mapCoordToIndex(x, y)].visible;
}

void FieldOfView::markAsVisible(long x, long y) {
    squares[mapCoordToIndex(x, y)].visible = true;
}

int FieldOfView::getViewWidthTiles(int resolutionX, int tileWidth) {
    int viewWidthInTiles = resolutionX / tileWidth;
    return viewWidthInTiles + 2;
}

int FieldOfView::getViewHeightTiles(int resolutionY, int tileWidth) {
    int viewHeightInTiles = resolutionY / tileWidth;
    return viewHeightInTiles + 2;
}

FieldOfView::FieldOfView(Creature* creature, const sf::RenderWindow& window, int tileWidth, WorldMap* worldMap) {
    start_angle = nullptr;
    end_angle = nullptr;
    allocated = 0;
    auto mapViewportWidth = float(1.f - CONSOLE_WIDTH);
    auto windowSize = window.getSize();
    this->creature = creature;
    cout << "Window size at FOV creation: " << windowSize.x << "x" << windowSize.y << endl;
    auto mapRenderSize = sf::Vector2i(static_cast<int>(windowSize.x * mapViewportWidth), windowSize.y);
    this->width = getViewWidthTiles(mapRenderSize.x, tileWidth);
    this->height = getViewHeightTiles(mapRenderSize.y, tileWidth);
    cout << "FOV map dimensions: " << this->width << "x" << this->height << endl;
    cout << "Creating FOV: (" << width << ", " << height << ")" << endl;
    cout << "FOV Top left: (" << left << ", " << top << ")" << endl;
    squares = vector<Cell>(static_cast<unsigned long>(width * height));
    cout << "Size of squares vector: " << squares.size() << endl;
    this->worldMap = worldMap;
}

void FieldOfView::invalidate(int tileWidth, const sf::RenderWindow& window) {
    auto mapViewportWidth = float(1.f - CONSOLE_WIDTH);
    auto windowSize = window.getSize();
    auto mapRenderSize = sf::Vector2f(windowSize.x * mapViewportWidth, windowSize.y);
    auto viewWidthInTiles = int(mapRenderSize.x / tileWidth);
    auto viewHeightInTiles = int(mapRenderSize.y / tileWidth);
    this->width = viewWidthInTiles;
    this->height = viewHeightInTiles;
    squares = vector<Cell>(static_cast<unsigned long>(width * height));
}

long FieldOfView::mapCoordToIndex(long x, long y) {
    x -= this->left;
    y -= this->top;
    auto out = (y * width) + x;
    if (out > squares.size())
        return false;
    return out;
}

void FieldOfView::update() {
    long square = 0;
    auto creatureLocation = creature->getLocation();
    this->left = creatureLocation.x - width / 2;
    this->top = creatureLocation.y - height / 2;
    for (long y = top; y < top + height; ++y) {
        for (long x = left; x < left + width; ++x) {
            squares[square].transparent = !worldMap->isOpaque(Point(x, y));
            ++square;
        }
    }
    for (auto cell : squares) {
        cell.visible = false;
    }
    int max_obstacles;
    /*first, zero the FOV map */
    for(long c = squares.size() - 1; c >= 0; --c) squares[c].visible = false;

    /*calculate an approximated (excessive, just in case) maximum number of obstacles per octant */
    max_obstacles = static_cast<int>(squares.size() / 7);

    if (max_obstacles > allocated) {
        allocated = max_obstacles;
        delete start_angle;
        delete end_angle;
        start_angle = new double[max_obstacles];
        end_angle = new double[max_obstacles];
    }

    /*set PC's position as visible */
    squares[mapCoordToIndex(creatureLocation.x, creatureLocation.y)].visible = true;

    /*compute the 4 quadrants of the map */
    int centerX = static_cast<int>(creatureLocation.x - left);
    int centerY = static_cast<int>(creatureLocation.y - top);
    computeQuadrant(centerX, centerY, 1, 1);
    computeQuadrant(centerX, centerY, 1, -1);
    computeQuadrant(centerX, centerY, -1, 1);
    computeQuadrant(centerX, centerY, -1, -1);
}

void FieldOfView::computeQuadrant(int player_x, int player_y, int dx, int dy) {
    FieldOfView* m = this;
    bool light_walls = true;
    int max_radius = 1000;
    /*octant: vertical edge */
    {
        int iteration = 1; /*iteration of the algo for this octant */
        bool done = false;
        int total_obstacles = 0;
        int obstacles_in_last_line = 0;
        double min_angle = 0.0;
        long x,y;

        /*do while there are unblocked slopes left and the algo is within the map's boundaries
          scan progressive lines/columns from the PC outwards */
        y = player_y+dy; /*the outer slope's coordinates (first processed line) */
        if (y < 0 || y >= m->height) done = true;
        while(!done) {
            /*process cells in the line */
            auto slopes_per_cell = 1.0 / double(iteration);
            double half_slopes = slopes_per_cell * 0.5;
            auto processed_cell = int((min_angle + half_slopes) / slopes_per_cell);
            long minx = MAX(0,player_x-iteration), maxx = MIN(m->width-1,player_x+iteration);
            done = true;
            for (x = player_x + (processed_cell * dx); x >= minx && x <= maxx; x+=dx) {
                long c = x + (y * m->width);
                /*calculate slopes per cell */
                bool visible = true;
                bool extended = false;
                double centre_slope = (double)processed_cell * slopes_per_cell;
                double start_slope = centre_slope - half_slopes;
                double end_slope = centre_slope + half_slopes;
                if (obstacles_in_last_line > 0 && !m->squares[c].visible) {
                    int idx = 0;
                    if ((!m->squares[c - (m->width * dy)].visible || !m->squares[c - (m->width * dy)].transparent) && (x - dx >= 0 && x - dx < m->width && (
                            !m->squares[c - (m->width * dy) - dx].visible || !m->squares[c - (m->width * dy) - dx].transparent))) visible = false;
                    else while(visible && idx < obstacles_in_last_line) {
                            if (start_angle[idx] > end_slope || end_angle[idx] < start_slope) {
                                ++idx;
                            }
                            else {
                                if (m->squares[c].transparent) {
                                    if (centre_slope > start_angle[idx] && centre_slope < end_angle[idx])
                                        visible = false;
                                }
                                else {
                                    if (start_slope >= start_angle[idx] && end_slope <= end_angle[idx])
                                        visible = false;
                                    else {
                                        start_angle[idx] = MIN(start_angle[idx],start_slope);
                                        end_angle[idx] = MAX(end_angle[idx],end_slope);
                                        extended = true;
                                    }
                                }
                                ++idx;
                            }
                        }
                }
                if (visible) {
                    m->squares[c].visible = true;
                    done = false;
                    /*if the cell is opaque, block the adjacent slopes */
                    if (!m->squares[c].transparent) {
                        if (min_angle >= start_slope) {
                            min_angle = end_slope;
                            /* if min_angle is applied to the last cell in line, nothing more
                               needs to be checked. */
                            if (processed_cell == iteration) done = true;
                        }
                        else if (!extended) {
                            start_angle[total_obstacles] = start_slope;
                            end_angle[total_obstacles++] = end_slope;
                        }
                        if (!light_walls) m->squares[c].visible = false;
                    }
                }
                processed_cell++;
            }
            if (iteration == max_radius) done = true;
            iteration++;
            obstacles_in_last_line = total_obstacles;
            y += dy;
            if (y < 0 || y >= m->height) done = true;
        }
    }
    /*octant: horizontal edge */
    {
        int iteration = 1; /*iteration of the algo for this octant */
        bool done = false;
        int total_obstacles = 0;
        int obstacles_in_last_line = 0;
        double min_angle = 0.0;
        long x,y;

        /*do while there are unblocked slopes left and the algo is within the map's boundaries
         scan progressive lines/columns from the PC outwards */
        x = player_x+dx; /*the outer slope's coordinates (first processed line) */
        if (x < 0 || x >= m->width) done = true;
        while(!done) {
            /*process cells in the line */
            double slopes_per_cell = 1.0 / (double)(iteration);
            double half_slopes = slopes_per_cell * 0.5;
            auto processed_cell = (int)((min_angle + half_slopes) / slopes_per_cell);
            long miny = MAX(0,player_y-iteration), maxy = MIN(m->height-1,player_y+iteration);
            done = true;
            for (y = player_y + (processed_cell * dy); y >= miny && y <= maxy; y+=dy) {
                long c = x + (y * m->width);
                /*calculate slopes per cell */
                bool visible = true;
                bool extended = false;
                double centre_slope = (double)processed_cell * slopes_per_cell;
                double start_slope = centre_slope - half_slopes;
                double end_slope = centre_slope + half_slopes;
                if (obstacles_in_last_line > 0 && !m->squares[c].visible) {
                    int idx = 0;
                    if ((!m->squares[c - dx].visible || !m->squares[c - dx].transparent) && (y - dy >= 0 && y - dy < m->height && (
                            !m->squares[c - (m->width * dy) - dx].visible || !m->squares[c - (m->width * dy) - dx].transparent))) visible = false;
                    else while(visible && idx < obstacles_in_last_line) {
                            if (start_angle[idx] > end_slope || end_angle[idx] < start_slope) {
                                ++idx;
                            }
                            else {
                                if (m->squares[c].transparent) {
                                    if (centre_slope > start_angle[idx] && centre_slope < end_angle[idx])
                                        visible = false;
                                }
                                else {
                                    if (start_slope >= start_angle[idx] && end_slope <= end_angle[idx])
                                        visible = false;
                                    else {
                                        start_angle[idx] = MIN(start_angle[idx],start_slope);
                                        end_angle[idx] = MAX(end_angle[idx],end_slope);
                                        extended = true;
                                    }
                                }
                                ++idx;
                            }
                        }
                }
                if (visible) {
                    m->squares[c].visible = true;
                    done = false;
                    /*if the cell is opaque, block the adjacent slopes */
                    if (!m->squares[c].transparent) {
                        if (min_angle >= start_slope) {
                            min_angle = end_slope;
                            /* if min_angle is applied to the last cell in line, nothing more
                                 needs to be checked. */
                            if (processed_cell == iteration) done = true;
                        }
                        else if (!extended) {
                            start_angle[total_obstacles] = start_slope;
                            end_angle[total_obstacles++] = end_slope;
                        }
                        if (!light_walls) m->squares[c].visible = false;
                    }
                }
                processed_cell++;
            }
            if (iteration == max_radius) done = true;
            iteration++;
            obstacles_in_last_line = total_obstacles;
            x += dx;
            if (x < 0 || x >= m->width) done = true;
        }
    }
}

void FieldOfView::castRay(Point from, Point to) {
    // Let's get Bresenheimy
//    cout << "Casting from (" << from.x << ", " << from.y << ") to (" << to.x << ", " << to.y << ")" << endl;
    bool swapXY = abs(to.y - from.y) > abs(to.x - from.x);
    long x0, y0, x1, y1;
    if (swapXY) {
        x0 = from.y;
        y0 = from.x;
        x1 = to.y;
        y1 = to.x;
    } else {
        x0 = from.x;
        y0 = from.y;
        x1 = to.x;
        y1 = to.y;
    }
    float deltaX = x1 - x0;
    float deltaY = abs(y1 - y0);
    float error = deltaX / 2;
    long y = y0;
    int stepY = -1;
    if (y0 < y1) stepY = 1;

    if (x1 > x0) { // X is increasing
        for (long x = x0; x <= x1; ++x) {
            if (swapXY) {
                markAsVisible(y, x);
                error -= deltaY;
                if (worldMap->isOpaque(Point(y, x))) {
                    return;
                }
            } else {
                markAsVisible(x, y);
                error -= deltaY;
                if (worldMap->isOpaque(Point(x, y))) {
                    return;
                }
            }
            if (error < 0) {
                y += stepY;
                error += deltaX;
            }
        }
    } else { // X is decreasing
        for (long x = x0; x >= x1; --x) {
            if (swapXY) {
                markAsVisible(y, x);
                error -= deltaY;
                if (worldMap->isOpaque(Point(y, x))) {
                    return;
                }
            } else {
                markAsVisible(x, y);
                error -= deltaY;
                if (worldMap->isOpaque(Point(x, y))) {
                    return;
                }
            }
            if (error < 0) {
                y -= stepY;
                error -= deltaX;
            }
        }
    }
}

