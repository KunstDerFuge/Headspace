#include <iostream>
#include <SFML/Graphics.hpp>
#include "World.h"
#include "Game.h"

using namespace std;

int main() {

    auto game = new Game();

    sf::RenderWindow window(sf::VideoMode(1024, 768), "Headspace");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    unsigned short frameCount = 0;
    sf::Clock clock;
    double lastTime = 0;

    while (window.isOpen()) {
        sf::Event event;
        ++frameCount;
        double currentTime = clock.getElapsedTime().asSeconds();
        double fps = 1.f / (currentTime - lastTime);
        lastTime = currentTime;

        if (frameCount % 64 == 0) {
            cout << "Current time: " << currentTime << endl;
            cout << "Last time: " << lastTime << endl;
            cout << "FPS: " << fps << endl;

//            int random = rand() % 5;
//            switch (random) {
//                case 0:
//                    game->logMessage("The jaguar bites!", warning);
//                    break;
//                case 1:
//                    game->logMessage("You drink some water.", positive);
//                    break;
//                case 2:
//                    game->logMessage("You feel cold.");
//                    break;
//                case 3:
//                    game->logMessage("You read the pamphlet, but don't learn anything interesting.");
//                    break;
//                case 4:
//                    game->logMessage("Peter coughs.");
//            }
        }

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered) {
                unsigned int key = event.text.unicode;
                bool moved = true;
                if (key == 'w' || key == 'k') {
                    moved = game->movePlayer(2);
                }
                if (key == 'a' || key == 'h') {
                    moved = game->movePlayer(0);
                }
                if (key == 's' || key == 'j') {
                    moved = game->movePlayer(1);
                }
                if (key == 'd' || key == 'l') {
                    moved = game->movePlayer(3);
                }
                if (!moved)
                    game->logMessage("Ouch!");
            }
        }

        // RENDER THE MAP
        window.clear(sf::Color(100, 100, 100));
        game->render(window);

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
    delete game;
    return 0;
}