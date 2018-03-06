//
// Created by main on 3/4/18.
//

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "FieldOfView.h"

using namespace std;

bool FieldOfView::isVisible(long x, long y) {
    return squares[mapCoordToIndex(x, y)];
}

void FieldOfView::update(Creature* creature) {
    int sum = 0;
    for (auto &&square : squares) {
        if (square == true)
            ++sum;
    }
    auto creatureLocation = creature->getLocation();
    this->left = creatureLocation.x - width / 2 - 1;
    this->top = creatureLocation.y - height / 2;
    fill(squares.begin(), squares.end(), false); // Set all squares to invisible

    // Cast rays along top and bottom of the screen
    for (long x = left; x < left+width; ++x) {
        castRay(creatureLocation, Point(x, top));
        castRay(creatureLocation, Point(x, top+height));
    }
    // Cast rays left and right
    for (long y = top; y < top+height; ++y) {
        castRay(creatureLocation, Point(left, y));
        castRay(creatureLocation, Point(left+width, y));
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

void FieldOfView::markAsVisible(long x, long y) {
    squares[mapCoordToIndex(x, y)] = true;
}

FieldOfView::FieldOfView(Creature* creature, const sf::RenderWindow& window, int tileWidth, WorldMap* worldMap) {
    auto mapViewportWidth = float(1.f - CONSOLE_WIDTH);
    auto creatureLocation = creature->getLocation();
    auto windowSize = window.getSize();
    cout << "Window size at FOV creation: " << windowSize.x << "x" << windowSize.y << endl;
    auto mapRenderSize = sf::Vector2f(windowSize.x * mapViewportWidth, windowSize.y);
    auto viewWidthInTiles = int(mapRenderSize.x / tileWidth);
    auto viewHeightInTiles = int(mapRenderSize.y / tileWidth);
    auto renderWidthInTiles = viewWidthInTiles + 2;
    auto renderHeightInTiles = viewHeightInTiles + 2;
    this->width = renderWidthInTiles;
    this->height = renderHeightInTiles;
    cout << "FOV map dimensions: " << this->width << "x" << this->height << endl;
    this->left = creatureLocation.x - renderWidthInTiles / 2;
    this->top = creatureLocation.y - renderHeightInTiles / 2;
    cout << "Creating FOV: (" << width << ", " << height << ")" << endl;
    cout << "FOV Top left: (" << left << ", " << top << ")" << endl;
    squares = vector<bool>(static_cast<unsigned long>(width * height));
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
    squares = vector<bool>(static_cast<unsigned long>(width * height));
}

long FieldOfView::mapCoordToIndex(long x, long y) {
    x -= this->left;
    y -= this->top;
    auto out = (y * width) + x;
    if (out > squares.size())
        return false;
    return out;
}
