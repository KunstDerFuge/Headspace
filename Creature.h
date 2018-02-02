//
// Created by KunstDerFuge on 1/23/18.
//

#ifndef HEADSPACE_CREATURE_H
#define HEADSPACE_CREATURE_H

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

class Body;

class Creature {
private:
    Body* body;

public:
    float getWeight();
    float getSize();
    Creature* generateRandom(int sizeClass);
    void setBody(Body* body);
};


#endif //HEADSPACE_CREATURE_H
