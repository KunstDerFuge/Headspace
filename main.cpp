#include <iostream>
#include <vector>
#include <random>
#include "Player.h"
#include "Utilities.h"
#include "Creature.h"
#include "Body.h"

using namespace std;

int main() {

    auto creature = new Creature;
    for (int i = 0; i < 100; i++)
        creature->generateRandom(randomChoiceOfN(5));

//    for (int i = 0; i < 50; i++)
//        cout << toOrdinal(i) << endl;

    auto body = new Body(10);
    for (int i = 0; i < 10; i++) {
        body->generateParts(100, LOCOMOTION_BIPEDAL, COMPOSITION_FLESH);
    }

    return 0;
}