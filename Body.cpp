//
// Created by KunstDerFuge on 1/24/18.
//

#include <list>
#include <vector>
#include <string>

#include "Body.h"
#include "Creature.h"
#include "strings.h"
#include "Utilities.h"

using namespace std;

Body::Body(std::list<BodyPart*> &parts, std::list<BodyRegion*> &regions, float size) {
    bodyRegions = regions;
    this->size = size;

    int totalWeight = 0;
    // Do fancy recursive stuff here
    weight = totalWeight;
}

/*
 * Generate a random new body for the species represented by these three parameters.
 */
void Body::generateParts(float size, int locomotion, int composition) {
    switch (locomotion) {
        case LOCOMOTION_BIPEDAL: {
            auto head = addBodyRegion(str_head, 1);
            auto torso = addBodyRegion(str_torso, 4);
            auto legs = addBodyRegion(str_legs, 4);

            // Head
            auto eyes = head->addSubRegion(str_eyes, 0.1);

            // Torso
            auto upperBody = torso->addSubRegion(str_upper_body, 0.5);
            auto lowerBody = torso->addSubRegion(str_lower_body, 0.5);

            // Legs
            legs->subdivideIntoParts(str_leg, 1.f, 2, true);
            legs->emptySpaceFactor = 0.3;

            for (auto leg : legs->subRegions) {
                //leg->addSubRegion()
            }

            break;
        }

        case LOCOMOTION_QUADRUPEDAL: {
            auto head = addBodyRegion(str_head, 2);
            auto torso = addBodyRegion(str_torso, 1);
            auto legs = addBodyRegion(str_legs, 2);
            break;
        }

        case LOCOMOTION_OCTOPEDAL: {
            auto cephalothorax = addBodyRegion(str_cephalothorax, 1);
            auto legs = addBodyRegion(str_legs, 1);
            break;
        }

        case LOCOMOTION_SLITHERING: {
            auto head = addBodyRegion(str_head, 1);
            auto body = addBodyRegion(str_body, 4);
            break;
        }

        case LOCOMOTION_GASTROPEDAL: {
            if (randomBool()) { // 50% chance gastropod has a shell
                // Snail-like
                auto shell = addBodyRegion(str_shell, 3);
            } else {
                // Sluglike
                auto mantle = addBodyRegion(str_cephalopod_mantle, 1);
            }
            auto cephalopodFoot = addBodyRegion(str_cephalopod_foot, 2);
            break;
        }

        case LOCOMOTION_TENTACLE_CRAWLING: {
            auto head = addBodyRegion(str_head, 1);
            auto tentacles = addBodyRegion(str_tentacles, 1);
            break;
        }

        case LOCOMOTION_FLYING: {
            auto wings = addBodyRegion(str_wings, 2);

            if (randomBool) { // 50% chance insectlike (segmented body), 50% batlike)
                // Insectlike
                auto head = addBodyRegion(str_head, 1);
                auto thorax = addBodyRegion(str_thorax, 2);
                auto abdomen = addBodyRegion(str_abdomen, 1);
            } else {
                // Batlike
                auto head = addBodyRegion(str_head, 1);
                auto body = addBodyRegion(str_body, 2);
            }
            break;
        }

        case LOCOMOTION_PSYCHIC: {
            break;
        }
    }
}

/*
 * Add a root-level body region to this body. Root-level regions will be shown to the user first when targeting,
 * e.g. 'Head', 'Body', 'Legs'.
 */
BodyRegion* Body::addBodyRegion(std::string name, float sizeWeight) {
    auto bodyRegion = new BodyRegion(name, sizeWeight);
    bodyRegions.push_back(bodyRegion);
    return bodyRegion;
}

/*
 * Add a physical body part to this body region. If a region contains no body parts, it is an abstract aiming area,
 * like 'Upper body'. Successful blows to an abstract region will land randomly on one of the sub-regions containing
 * physical parts.
 */
void Body::addBodyPart(BodyPart *part) {

}

BodyRegion::BodyRegion(std::string name, float sizeWeight) {
    this->name = name;
    this->size = size;
}

/*
 * Add new sub-region to this body region. NOTE: Unlike Body::addBodyRegion, this weight will not be normalized, it
 * represents a fraction of the area of its parent. For example, a BodyRegion 'head' may have a single subregion
 * 'eyes' with weight 0.1, meaning the eyes are 10% the target area of the head, the other 90% being just head.
 */
BodyRegion *BodyRegion::addSubRegion(std::string name, float sizeFraction, std::string positionName) {
    auto child = new BodyRegion(name, sizeFraction);
    child->positionName = concatenateWord(this->positionName, positionName);
    this->subRegions.push_back(child);
    return child;
}

/*
 * Add an attached region to this body region. Attached regions do not overlap at all, and their size is a weighted
 * value that will be normalized at the end of creation. If the 'head' region has weight 1, and an 'upperBody'
 * region has weight 4, the upper body's target area is equivalent to four heads. The creature's total size will then be
 * distributed amongst its regions accordingly.
 */
BodyRegion *BodyRegion::addAttachedRegion(std::string name, float sizeWeight) {
    auto attachment = new BodyRegion(name, sizeWeight);
    this->attachedRegions.push_back(attachment);
    return attachment;
}

/*
 * Subdivide parent region into N equal parts, useful for groups of identical limbs. SizeFraction here is the fraction
 * of the parent's area that the entire group takes up. In most cases this will be 1.0 unless there is another type of
 * limb subdividing the same region.
 */
BodyRegion *BodyRegion::subdivideIntoParts(string name, float sizeFraction, int numberOfSubdivisions, bool useLeftRight) {
    float areaPerSubdivision = sizeFraction / numberOfSubdivisions;
    if (!positionName.empty())
        positionName += ' ';
    for (int i = 0; i < numberOfSubdivisions; i++) {
        string subdivisionName = positionName;
        if (numberOfSubdivisions == 3 && useLeftRight) {
            if (i == 0) {
                subdivisionName += "left ";
            } else if (i == 1) {
                subdivisionName += "middle ";
            } else if (i == 2) {
                subdivisionName += "right ";
            }
        } else if (numberOfSubdivisions == 2 && useLeftRight) {
            if (i == 0) {
                subdivisionName += "left ";
            } else {
                subdivisionName += "right ";
            }
        } else {
            subdivisionName += toOrdinal(i) + ' ';
        }
        subdivisionName += name;
        this->addSubRegion(subdivisionName, areaPerSubdivision);
    }
}

BodyRegion *BodyRegion::connectExistingRegion(BodyRegion *child) {
    this->attachedRegions.push_back(child);
    return child;
}

void BodyPart::addChild(BodyRegion* child) {
    children.push_back(child);
}

void BodyPart::addInternal(BodyPart *internal) {
    internalParts.push_back(internal);
}