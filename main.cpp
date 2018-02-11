#include <iostream>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Utilities.h"
#include "Creature.h"
#include "Body.h"

using namespace std;

int main() {

    sf::RenderWindow window(sf::VideoMode(200, 200), "Poop all over me!");
    sf::CircleShape shape(100);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(shape);
        window.display();
    }

    auto creature = new Creature(Point(0, 0));
    for (int i = 0; i < 100; i++)
        creature->generateRandom(randomChoiceOfN(5));

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