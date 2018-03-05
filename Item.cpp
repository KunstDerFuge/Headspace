//
// Created by KunstDerFuge on 1/23/18.
//

#include "Item.h"

using namespace std;

float Item::getWeight() {
    return weight;
}

Item::Item(const std::string& name, const std::string& description, float weight) {
    this->name = name;
    this->description = description;
    this->weight = weight;
}
