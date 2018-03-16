//
// Created by KunstDerFuge on 2/28/18.
//

#ifndef HEADSPACE_GAME_H
#define HEADSPACE_GAME_H


#include "World.h"
#include "Console.h"

class Game {
private:
    World* world;
    Console* console;
    sf::RenderTexture mapWindow;
public:
    void logMessage(std::wstring message, message_type type=info);
    bool movePlayer(direction dir);
    Player* getPlayer() {return world->getPlayer();}
    Console* getConsole() {return console;}
    std::vector<Creature*> getCreaturesAt(Point location, WorldMap* worldMap);
    void render(sf::RenderWindow& window);
    sf::RenderTexture& getMapWindow();
    void resizeMapWindow(sf::RenderWindow& window);

    explicit Game(const sf::RenderWindow& window);
    ~Game();
};


#endif //HEADSPACE_GAME_H
