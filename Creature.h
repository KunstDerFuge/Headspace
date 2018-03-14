//
// Created by KunstDerFuge on 1/23/18.
//

#ifndef HEADSPACE_CREATURE_H
#define HEADSPACE_CREATURE_H

#include "WorldMap.h"

static const int COMPOSITION_FLESH = 0;
static const int COMPOSITION_GELATINOUS = 1;
static const int COMPOSITION_MUCOUSY_COLLAGEN = 2;  // Think octopus
static const int COMPOSITION_SCALES_TOUGH = 3;
static const int COMPOSITION_SCALES_SLIMY = 4;
static const int COMPOSITION_CHITINOUS = 5;
static const int NUM_COMPOSITIONS = 6;

static const int LOCOMOTION_BIPEDAL = 0;
static const int LOCOMOTION_QUADRUPEDAL = 1;
static const int LOCOMOTION_OCTOPEDAL = 2;
static const int LOCOMOTION_SLITHERING = 3;
static const int LOCOMOTION_GASTROPEDAL = 4;
static const int LOCOMOTION_TENTACLE_CRAWLING = 5;
static const int LOCOMOTION_FLYING = 6;
static const int LOCOMOTION_PSYCHIC = 7;
static const int NUM_LOCOMOTIONS = 8;

static const int ABILITY_BITE = 0;
static const int ABILITY_CLAW = 0;
static const int ABILITY_SCRATCH = 0;
static const int ABILITY_SECRETE_ACID = 0;
static const int ABILITY_BLOODSUCKING_ = 0;
static const int ABILITY_TELEKINESIS = 0;

static const int SIZE_TINY = 0;
static const int SIZE_SMALL = 1;
static const int SIZE_MEDIUM = 2;
static const int SIZE_LARGE = 3;
static const int SIZE_COLOSSAL = 4;

enum AbilityTag { vision, hearing, presence_vibration_detect, smell, telepathy,   // senses
                    movement, flight, grasp, tentacle_grasp,
                    bite, scratch, bash, secrete_acid, bloodsucking, telekinesis };

class Body;
class VisibleMap;

class Creature {
protected:
    Body* body;
    Point location;
    WorldMap* worldMap;
public:
    float getWeight();
    float getSize();
    Creature* generateRandom(int sizeClass, WorldMap* worldMap);
    void setBody(Body* body);
    Creature(Point location, WorldMap* worldMap);
    Point getLocation();
    WorldMap* getWorldMap();
    Point getAdjacentPoint(direction dir);
    void render(sf::Texture* texture, VisibleMap* visibleMap, sf::RenderWindow& window);
};


#endif //HEADSPACE_CREATURE_H
