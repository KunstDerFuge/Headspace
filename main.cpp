#include <iostream>
#include <SFML/Graphics.hpp>
#include "World.h"

using namespace std;

int main() {

    auto world = new World(3);

    sf::RenderWindow window(sf::VideoMode(1024, 768), "Headspace");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // RENDER THE MAP
        window.clear(sf::Color(0, 100, 100));
        world->renderMap(window);

        // Display
        window.display();
    }

//    auto creature = new Creature(Point(0, 0));
//    for (int i = 0; i < 100; i++)
//        creature->generateRandom(randomChoiceOfN(5));
//
//    auto body = new Body(10);
//    for (int i = 0; i < 1; i++) {
//        body->generateParts(100, LOCOMOTION_BIPEDAL, COMPOSITION_FLESH);
//    }
//    auto parts = body->printWalkthrough();
//
//    int selection;
//    while(true) {
//        cin >> selection;
//
//        parts = body->printWalkthrough(parts[selection]);
//
//        if (selection == -1)
//            break;
//    }
    delete world;
    return 0;
}