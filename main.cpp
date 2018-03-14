#include <iostream>
#include <SFML/Graphics.hpp>
#include "World.h"
#include "Game.h"

using namespace std;

int main() {

    sf::RenderWindow window(sf::VideoMode(1024, 768), "Headspace");
    auto game = new Game(window);

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    unsigned short frameCount = 0;
    sf::Clock clock;
    double lastTime = 0;

    while (window.isOpen()) {
//        game->getPlayer()->move(3);
        sf::Event event;
        ++frameCount;
        double currentTime = clock.getElapsedTime().asMicroseconds();
        auto diff = static_cast<int>(currentTime - lastTime);
        double fps = 1000000.f / (currentTime - lastTime);
        lastTime = currentTime;
        if (frameCount % 64 == 0) {
            cout << "Current time: " << currentTime << endl;
            cout << "Last time: " << lastTime << endl;
            cout << "FPS: " << fps << endl;

            int random = rand() % 5;
            switch (random) {
                case 0:
                    game->logMessage(L"The jaguar bites!", warning);
                    break;
                case 1:
                    game->logMessage(L"You drink some water.", positive);
                    break;
                case 2:
                    game->logMessage(L"Юрий Гагарин");
                    break;
                case 3:
                    game->logMessage(L"You read the pamphlet, but don't learn anything interesting. Then again, why would you? It's not like you are really that interested in pamphlets in the first place, so why even read it? You ponder this for a while, and eventually settle on the conclusion that, because you're on an isolated planet without any other means of stimulation, at some point reading a pamphlet seemed like a decent idea.");
                    break;
                case 4:
                    game->logMessage(L"Peter coughs.");
            }
        }

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered) {
                unsigned int key = event.text.unicode;
                bool moved = true;
                if (key == 'w' || key == 'k') {
                    moved = game->movePlayer(north);
                }
                if (key == 'a' || key == 'h') {
                    moved = game->movePlayer(west);
                }
                if (key == 's' || key == 'j') {
                    moved = game->movePlayer(south);
                }
                if (key == 'd' || key == 'l') {
                    moved = game->movePlayer(east);
                }
                if (key == 'y' || key == '7') {
                    moved = game->movePlayer(northwest);
                }
                if (!moved)
                    game->logMessage(L"Ouch!");
            }
            if (event.type == sf::Event::Resized) {
                game->getPlayer()->shouldRedrawMap = true;
                game->getPlayer()->resizeFOV(window);
                game->getPlayer()->resizeVisible();
            }
        }

        // RENDER THE MAP
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