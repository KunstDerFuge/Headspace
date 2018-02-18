#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "WorldMap.h"

using namespace std;

int main() {

    sf::RenderWindow window(sf::VideoMode(1024, 768), "Headspace");
    sf::Texture texture;
    if (!texture.loadFromFile("../assets/graphics/sample.png"))
        cout << "Could not load texture" << endl;

    sf::CircleShape circleShape(300);

    sf::Shader shader;
    circleShape.setFillColor(sf::Color::Green);
    //circleShape.setTexture(&texture);
    circleShape.setTexture(&texture);

    if (!shader.loadFromFile("../assets/shaders/retro_texture.frag", sf::Shader::Fragment)) {
        cerr << "Could not load shader" << endl;
    }

    sf::RenderTexture screen;
    if (!screen.create(1000, 1000)) {
        cerr << "Could not create render texture" << endl;
        return 1;
    }

    screen.clear();
    screen.draw(circleShape, &shader);
    screen.display();
    sf::Sprite sprite(screen.getTexture());
    shader.setUniform("Texture", sf::Texture(*sprite.getTexture()));

    WorldMap worldMap(30);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color(0, 100, 100));
        window.draw(sprite);
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

    return 0;
}