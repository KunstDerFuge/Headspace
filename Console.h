//
// Created by KunstDerFuge on 2/28/18.
//

#ifndef HEADSPACE_CONSOLE_H
#define HEADSPACE_CONSOLE_H

#include <string>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

enum vga_color {
    black = 0x000000FF,
    red = 0xAA0000FF,
    green = 0x00AA00FF,
    brown = 0xAA5500FF,
    blue = 0x0000AAFF,
    magenta = 0xAA00AAFF,
    cyan = 0x00AAAAFF,
    gray = 0xAAAAAAFF,
    dark_gray = 0x555555FF,
    light_red = 0xFF5555FF,
    light_green = 0x55FF55FF,
    light_yellow = 0xFFFF55FF,
    light_blue = 0x55FFFFFF,
    light_magenta = 0xFF55FFFF,
    light_cyan = 0x85FFFFFF,
    white = 0xFFFFFFFF
};

enum message_type {
    info, warning, serious, positive
};

struct Message {
    std::wstring message;
    message_type type;
    int count;
    Message(std::wstring message, message_type type) {
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
    void logMessage(std::wstring& message, message_type& type);
    Message& getLastMessage();
    void render(sf::RenderWindow& window);
    std::wstring getMessageString(int i) const;
    message_type getMessageType(int i) const;
    sf::Color getMessageColor(message_type type) const;
    Console();

    float getNumLines(sf::Text& text);
    void wrapText(sf::Text& text, int rightBound);
    sf::Color getColor(vga_color color) const;
};


#endif //HEADSPACE_CONSOLE_H
