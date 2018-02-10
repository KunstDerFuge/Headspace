#include <iostream>
#include <vector>
#include <random>
#include "Player.h"
#include "Utilities.h"
#include "Creature.h"
#include "Body.h"

using namespace std;

int main() {

    auto creature = new Creature(Point(0, 0));
    for (int i = 0; i < 100; i++)
        creature->generateRandom(randomChoiceOfN(5));

//    for (int i = 0; i < 50; i++)
//        cout << toOrdinal(i) << endl;

    auto body = new Body(10);
    for (int i = 0; i < 1; i++) {
        body->generateParts(100, LOCOMOTION_BIPEDAL, COMPOSITION_FLESH);
    }
    auto parts = body->printWalkthrough();

    int selection;
    while(true) {
        cin >> selection;

        parts = body->printWalkthrough(parts[selection]);

        if (selection == -1)
            break;
    }

    return 0;
}