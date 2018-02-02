#include <iostream>
#include <vector>
#include <random>
#include "Player.h"
#include "Utilities.h"
#include "Creature.h"

using namespace std;

int main() {

    auto creature = new Creature;
    for (int i = 0; i < 100; i++)
        creature->generateRandom(randomChoiceOfN(5));

//    for (int i = 0; i < 50; i++)
//        cout << toOrdinal(i) << endl;

    return 0;
}