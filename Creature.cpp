//
// Created by KunstDerFuge on 1/23/18.
//

#include <iostream>
#include <vector>
#include <tgmath.h>

#include "Creature.h"
#include "Body.h"
#include "Utilities.h"


using namespace std;


float Creature::getWeight() {
    return body->weight;
}

float Creature::getSize() {
    return body->size;
}

Creature *Creature::generateRandom(int sizeClass) {

    float size;
    int locomotion;
    int composition;
    list<string> tags;

    switch (sizeClass) {
        case SIZE_TINY:
            size = randomSampleNormal(12, 2, 6, 20);
            locomotion = randomChoiceFromWeights( {1, 3, 4, 3, 6, 6, 0, 1} ); // Weights for each respective type of locomotion
            break;

        case SIZE_SMALL:
            size = randomSampleNormal(576, 144, 20, 864);
            locomotion = randomChoiceFromWeights( {3, 4, 4, 3, 4, 6, 4, 1} );
            break;

        case SIZE_MEDIUM:
            size = randomSampleNormal(1152, 144, 864, 1440);
            locomotion = randomChoiceFromWeights( {4, 5, 2, 2, 2, 3, 1, 1} );
            break;

        case SIZE_LARGE:
            size = randomSampleNormal(2592, 288, 1440, 4032);
            locomotion = randomChoiceFromWeights( {3, 5, 1, 1, 2, 2, 1, 1} );
            break;

        case SIZE_COLOSSAL:
            size = randomSampleNormal(14400, 432, 10000, 72000);
            locomotion = randomChoiceFromWeights( {2, 2, 1, 1, 1, 1, 1, 1} );
            break;

        default:
            cerr << "Unknown size class: " << sizeClass << endl;
            throw;
    }

    auto* creature = new Creature(Point(0, 0));
    list<BodyPart*> parts;
    list<BodyRegion*> regions;

    switch (locomotion) {
        // flesh, gelatinous, mucousy, tough scales, slimy scales, chitin
        case LOCOMOTION_BIPEDAL:
        case LOCOMOTION_QUADRUPEDAL:
            composition = randomChoiceFromWeights( {5, 0, 1, 2, 2, 1} );
            break;

        case LOCOMOTION_OCTOPEDAL:
            composition = randomChoiceFromWeights( {1, 0, 0, 0, 0, 5} );
            break;

        case LOCOMOTION_SLITHERING:
            composition = randomChoiceFromWeights( {2, 2, 5, 3, 4, 0} );
            break;

        case LOCOMOTION_GASTROPEDAL:
            composition = randomChoiceFromWeights( {0, 1, 5, 1, 1, 0} );
            break;

        case LOCOMOTION_TENTACLE_CRAWLING:
            composition = randomChoiceFromWeights( {0, 1, 4, 2, 3, 0} );
            break;

        case LOCOMOTION_FLYING:
            composition = randomChoiceFromWeights( {3, 0, 2, 2, 2, 0} );
            break;

        case LOCOMOTION_PSYCHIC:
            composition = randomChoiceFromWeights( {1, 1, 1, 1, 1, 1} );
            break;

        default:
            cerr << "Unknown locomotion type: " << locomotion << endl;
            throw;
    }

    //creature->body = new Body();

    vector<string> sizeClassVect = {"Tiny", "Small", "Medium", "Large", "Colossal"};
    vector<string> types = {"terrestrial", "snakelike", "amphibious", "fishy", "lizardlike", "snail", "crab", "blob"};
    vector<string> locomotionVect = {"Bipedal", "Quadripedal", "Octopedal", "Slithering", "Gastropedal", "Tentacle crawling", "Flying", "Psychic"};
    vector<string> compositionVect = {"Flesh", "Gelatinous", "Mucousy", "Tough scales", "Slimy scales", "Chitin"};

    cout << "Size: " << size << " in^2" << endl;
    cout << "Size class: " << sizeClassVect[sizeClass] << endl;
    cout << "Locomotion: " << locomotionVect[locomotion] << endl;
    cout << "Composition: " << compositionVect[composition] << endl;
    cout << endl;

    return nullptr;


    //body = new Body(0, 0, 0);
}

void Creature::setBody(Body* body) {
    this->body = body;
}

Creature::Creature(Point location) : location(location) {
}

