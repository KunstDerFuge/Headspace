//
// Created by KunstDerFuge on 1/24/18.
//

#ifndef HEADSPACE_BODY_H
#define HEADSPACE_BODY_H

#include <list>
#include <string>
#include <set>

#include "Creature.h"

struct BodyRegion;

struct BodyPart {
    std::vector<BodyPart*> internalParts;
    std::vector<BodyRegion*> children;
    float absoluteSize;
    float weightedSize;
    float targetSize;
    float weight;
    bool internal;
    void addChild(BodyRegion* child);
    void addInternal(BodyPart* internal);
};

struct Bone : BodyPart {
    bool cartilage;
};

struct Artery : BodyPart {

};

struct Muscle : BodyPart {

};

struct Organ : BodyPart {

};

struct Appendage : BodyPart {
    bool canGrip;
    bool prehensile;
};

struct Skin : BodyPart {
    int composition;
    float thickness;
};

struct Carapace : BodyPart {

};

struct BodyRegion {
/*
 * A body region represents a targetable region of a body. It may contain other body regions, which may in turn contain
 * physical parts. When targeting a large, abstract region, a successful blow will travel recursively down random body
 * regions until landing on one or more actual body parts.
 */
    BodyRegion(std::string name, float size, float emptySpaceFactor=0, bool targetable=true);
    std::vector<BodyPart*> parts;
    std::vector<BodyRegion*> subRegions;
    std::vector<BodyRegion*> attachedRegions;
    std::set<std::pair<AbilityTag, float>> abilityTags;
    float emptySpaceFactor;
    float size;
    bool targetable;
    std::string name;
    std::string positionName;
    std::string verbosePositionName;

    BodyRegion* addSubRegion(std::string name, float sizeFraction, std::string positionName="", bool usePossessive=false);
    BodyRegion* connectTo(BodyRegion *child);
    std::vector<BodyRegion*> subdivideIntoParts(std::string name, float sizeFraction, int numberOfSubdivisions, bool useLeftRight, bool usePossessive=false);
    void addAbility(AbilityTag ability, float factor);

    // Specialty functions for generating body parts
    BodyRegion* generateEyes(int minNumber, int maxNumber, float sizeFraction, float sharpnessMean, float sharpnessDev);

    std::string getName(bool noPosition=false);
    std::string getNameVerbose();
};

struct Body {
/*
 * A body is composed of a group of targetable body regions.
 */
    Body(float);
    std::vector<BodyRegion*> bodyRegions;
    BodyRegion* root;

    void generateParts(float size, int locomotion, int composition);
    std::vector<BodyRegion*> printWalkthrough(BodyRegion* region=nullptr);
    BodyRegion* addBodyRegion(std::string name, float sizeWeight, float emptySpaceFactor=0, bool targetable=true);
    void setAsRoot(BodyRegion* root);
    void addBodyPart(BodyPart* part);
    void calculateWeight();
    float size;
    float weight;
};


#endif //HEADSPACE_BODY_H
