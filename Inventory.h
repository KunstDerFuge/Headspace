//
// Created by KunstDerFuge on 1/23/18.
//

#include <list>

#ifndef HEADSPACE_INVENTORY_H
#define HEADSPACE_INVENTORY_H

class Item;

class Inventory {
private:
    std::list<Item*> items;

public:
    bool addItem(Item* item);
    int getTotalWeight();
};


#endif //HEADSPACE_INVENTORY_H
