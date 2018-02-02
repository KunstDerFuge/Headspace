//
// Created by KunstDerFuge on 1/23/18.
//

#include <list>

#include "Inventory.h"
#include "Item.h"

using namespace std;

bool Inventory::addItem(Item *item) {
    items.push_back(item);
}

int Inventory::getTotalWeight() {
    int weight = 0;
    for (auto item : items) {
        weight += item->getWeight();
    }
}
