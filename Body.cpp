//
// Created by KunstDerFuge on 1/24/18.
//

#include <vector>
#include <string>
#include <iostream>

#include "Body.h"
#include "Creature.h"
#include "strings.h"
#include "Utilities.h"

using namespace std;

Body::Body(float size) {
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
            auto arms = addBodyRegion(str_arms, 2, false);
            auto torso = addBodyRegion(str_torso, 4);
            auto legs = addBodyRegion(str_legs, 4, 0.3);

            // Head
            float hearingSharpness = randomSampleNormal(0.8, 0.2, 0.f, 1.f);
            float smellingSharpness = randomSampleNormal(0.5, 0.2, 0.f, 1.f);
            float biteAptitude = randomSampleNormal(0.2, 0.1, 0.f, 1.f);
            head->addAbility(hearing, hearingSharpness);
            head->addAbility(smell, smellingSharpness);
            head->addAbility(bite, biteAptitude);
            head->generateEyes(0, 3, 0.1, 0.5, 0.2);
            auto neck = head->addSubRegion(str_neck, 0.2);
            setAsRoot(head);
            head->connectExistingRegion(neck);

            // Torso
            auto upperBody = torso->addSubRegion(str_upper_body, 0.5);
            auto lowerBody = torso->addSubRegion(str_lower_body, 0.5);
            neck->connectExistingRegion(upperBody);
            upperBody->connectExistingRegion(lowerBody);

            // Arms
            auto armsPhysical = arms->subdivideIntoParts(str_arm, 1.f, 2, true);
            for (auto arm : armsPhysical) {
                auto upperArm = arm->addSubRegion(str_upper_arm, 0.45);
                auto lowerArm = arm->addSubRegion(str_lower_arm, 0.45);
                auto hand = arm->addSubRegion(str_hand, 0.1);
                auto palm = hand->addSubRegion(str_palm, 0.5);
                auto fingers = hand->addSubRegion(str_fingers, 0.5);
                int numFingers = randomFromXToY(2, 6);
                auto fingersLimbs = fingers->subdivideIntoParts(str_finger, 1.f, numFingers, false);
                upperBody->connectExistingRegion(upperArm)
                        ->connectExistingRegion(lowerArm)
                        ->connectExistingRegion(palm);
                for (auto finger : fingersLimbs) {
                    palm->connectExistingRegion(finger);
                    finger->addAbility(grasp, 0.2);
                }
                lowerArm->addAbility(movement, 0.2);
            }

            // Legs
            auto legsLimbs = legs->subdivideIntoParts(str_leg, 1.f, 2, true);

            for (auto leg : legsLimbs) {
                auto upperLeg = leg->addSubRegion(str_upper_leg, 0.48);
                auto lowerLeg = leg->addSubRegion(str_lower_leg, 0.48);
                auto foot = leg->addSubRegion(str_foot, 0.04);
                lowerBody->connectExistingRegion(upperLeg)
                    ->connectExistingRegion(lowerLeg)
                    ->connectExistingRegion(foot);
                foot->addAbility(movement, 0.6);
                foot->addAbility(presence_vibration_detect, 0.05);
            }

            break;
        }

        case LOCOMOTION_QUADRUPEDAL: {
            auto head = addBodyRegion(str_head, 1);
            auto torso = addBodyRegion(str_torso, 3);
            auto legs = addBodyRegion(str_legs, 2, 0.7);

            // Head
            auto eyes = head->addSubRegion(str_eyes, 0.1);
            auto neck = head->addSubRegion(str_neck, 0.4);
            setAsRoot(head);
            head->connectExistingRegion(neck);

            // Torso
            auto upperBody = torso->addSubRegion(str_upper_body, 0.5);
            auto lowerBody = torso->addSubRegion(str_lower_body, 0.5);
            neck->connectExistingRegion(upperBody);
            upperBody->connectExistingRegion(lowerBody);

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
 * e.g. 'Head', 'Body', 'Legs'. SizeWeight represents the weighted portion of the creature's target area contained in
 * this region. If the 'head' region has weight 1, and an 'upperBody' region has weight 4, the upper body's target area
 * is equivalent to four heads. The creature's total size will then be distributed amongst its regions accordingly.
 */
BodyRegion* Body::addBodyRegion(std::string name, float sizeWeight, float emptySpaceFactor, bool targetable) {
    auto bodyRegion = new BodyRegion(name, sizeWeight, emptySpaceFactor, targetable);
    bodyRegions.push_back(bodyRegion);
    return bodyRegion;
}

/*
 * Add a physical body part to this body region. If a region contains no body parts, it is an abstract targeting area,
 * like 'Upper body'. Successful blows to an abstract region will land randomly on one of the sub-regions containing
 * physical parts.
 */
void Body::addBodyPart(BodyPart *part) {

}

void Body::setAsRoot(BodyRegion* root) {
    this->root = root;
}

vector<BodyRegion*> Body::printWalkthrough(BodyRegion* region) {
    int count = 0;
    if (region != nullptr) {
        if (region->subRegions.empty()) {
            cout << "No subregions!" << endl;
            return region->subRegions;
        }
        for (auto part : region->subRegions) {
            cout << count << ": " << part->getName() << " (" << part->getNameVerbose() << ")" << endl;
            count++;
        }
        return region->subRegions;
    }
    for (auto part : bodyRegions) {
        cout << count << ": " << part->name << endl;
        count++;
    }
    return bodyRegions;
}

BodyRegion::BodyRegion(std::string name, float sizeWeight, float emptySpaceFactor, bool targetable) {
    this->name = name;
    this->size = size;
    this->emptySpaceFactor = emptySpaceFactor;
    this->targetable = targetable;
}

/*
 * Add new sub-region to this body region. NOTE: Unlike Body::addBodyRegion, this weight will not be normalized, it
 * represents a fraction of the area of its parent. For example, a BodyRegion 'head' may have a single subregion
 * 'eyes' with weight 0.1, meaning the eyes are 10% the target area of the head, the other 90% being just head.
 */
BodyRegion *BodyRegion::addSubRegion(std::string name, float sizeFraction, std::string positionName) {
    auto child = new BodyRegion(name, sizeFraction);
    child->positionName = positionName;
    child->verbosePositionName = concatenateWordToCopy(this->verbosePositionName, positionName);
    child->name = name;
    toSentenceCase(child->name);
    this->subRegions.push_back(child);
    return child;
}

/*
 * Subdivide parent region into N equal parts, useful for groups of identical limbs. SizeFraction here is the fraction
 * of the parent's area that the entire group takes up. In most cases this will be 1.0 unless there is another type of
 * limb subdividing the same region. UseLeftRight determines whether the subregions will be differentiated by
 * named positions left-center-right or first-second-third for groups of three or fewer.
 */
vector<BodyRegion*> BodyRegion::subdivideIntoParts(string name, float sizeFraction, int numberOfSubdivisions, bool useLeftRight) {
    float areaPerSubdivision = sizeFraction / numberOfSubdivisions;
    vector<BodyRegion*> parts;
    for (int i = 0; i < numberOfSubdivisions; i++) {
        string partName = name;
        string childPositionName = namePosition(i, numberOfSubdivisions, useLeftRight);
        auto newPart = this->addSubRegion(partName, areaPerSubdivision, childPositionName);
        parts.push_back(newPart);
    }
    return parts;
}

BodyRegion *BodyRegion::connectExistingRegion(BodyRegion *child) {
    this->attachedRegions.push_back(child);
    return child;
}

void BodyRegion::addAbility(AbilityTag ability, float factor) {
    abilityTags.insert( {ability, factor} );
}

std::string BodyRegion::getName(bool noPosition) {
    if (noPosition)
        return name;

    string out = concatenateWordToCopy(positionName, name);
    toSentenceCase(out);
    return out;
}

std::string BodyRegion::getNameVerbose() {
    string out = concatenateWordToCopy(verbosePositionName, name);
    toSentenceCase(out);
    return out;
}

BodyRegion* BodyRegion::generateEyes(int minNumber, int maxNumber, float sizeFraction, float sharpnessMean, float sharpnessDev) {
    int numberOfEyes = randomFromXToY(minNumber, maxNumber);
    if (numberOfEyes != 0) {
        float visionSharpnessPerEye = randomSampleNormal(sharpnessMean, sharpnessDev, 0.f, 1.f);
        auto eyes = this->addSubRegion(str_eyes, sizeFraction);
        auto eyesPhysical = eyes->subdivideIntoParts(str_eye, 1.f, numberOfEyes, true);
        for (auto eye : eyesPhysical)
            eye->addAbility(vision, visionSharpnessPerEye);

        return eyes;
    }
    return nullptr;
}

void BodyPart::addChild(BodyRegion* child) {
    children.push_back(child);
}

void BodyPart::addInternal(BodyPart *internal) {
    internalParts.push_back(internal);
}