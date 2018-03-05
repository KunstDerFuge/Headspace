//
// Created by KunstDerFuge on 1/23/18.
//

#ifndef HEADSPACE_ITEM_H
#define HEADSPACE_ITEM_H

#include <string>

class Item {
private:
    float weight;
    std::string name;
    std::string description;

public:
    float getWeight();
    Item(const std::string& name, const std::string& description, float weight);
};


#endif //HEADSPACE_ITEM_H
