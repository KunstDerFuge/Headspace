//
// Created by KunstDerFuge on 1/24/18.
//

#ifndef HEADSPACE_BODY_H
#define HEADSPACE_BODY_H

#include <list>
#include <string>

struct BodyRegion;

struct BodyPart {
    std::list<BodyPart*> internalParts;
    std::list<BodyRegion*> children;
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
    BodyRegion(std::string name, float size);
    std::list<BodyPart*> parts;
    std::list<BodyRegion*> subRegions;
    std::list<BodyRegion*> attachedRegions;
    float emptySpaceFactor;
    float size;
    std::string name;
    std::string positionName;

    BodyRegion* addSubRegion(std::string name, float sizeFraction, std::string positionName="");
    BodyRegion* addAttachedRegion(std::string name, float sizeWeight);
    BodyRegion* connectExistingRegion(BodyRegion* child);
    BodyRegion* subdivideIntoParts(std::string name, float sizeFraction, int numberOfSubdivisions, bool useLeftRight);
    BodyRegion* attachSymmetricalLimbs(std::string name, float sizeWeight, int numberOfLimbs, bool useLeftRight);
};

struct Body {
/*
 * A body is composed of a group of targetable body regions.
 */
    Body(std::list<BodyPart*>&, std::list<BodyRegion*>&, float);
    std::list<BodyRegion*> bodyRegions;
    BodyRegion* root;

    void generateParts(float size, int locomotion, int composition);
    BodyRegion* addBodyRegion(std::string name, float sizeWeight);
    void setAsRoot(BodyRegion* root);
    void addBodyPart(BodyPart* part);
    void calculateWeight();
    float size;
    float weight;
};


#endif //HEADSPACE_BODY_H
