//
// Created by main on 2/28/18.
//

#ifndef HEADSPACE_CONSOLE_H
#define HEADSPACE_CONSOLE_H

#include <string>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

enum message_type {
    info, warning, serious, positive
};

struct Message {
    std::string message;
    message_type type;
    int count;
    Message(std::string message, message_type type) {
        this->message = message;
        this->type = type;
        count = 1;
    }
};

class Console {
private:
    std::vector<Message> messages;
    sf::Font font;
public:
    void logMessage(std::string& message, message_type& type);
    Message& getLastMessage();
    void render(sf::RenderWindow& window);
    std::string getMessageString(int i) const;
    message_type getMessageType(int i) const;
    sf::Color getMessageColor(message_type type) const;
    Console();

    float getNumLines(sf::Text& text);
    void wrapText(sf::Text& text, int rightBound);
};


#endif //HEADSPACE_CONSOLE_H
