//
// Created by KunstDerFuge on 2/28/18.
//

#include <string>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <sstream>

#include "Console.h"
#include "WorldMap.h"
#include "Utilities.h"

using namespace std;

void Console::logMessage(std::wstring& message, message_type& type) {
    if (messages.empty()) { // Calling getLastMessage() with no messages will crash
        messages.emplace_back(message, type);
        return;
    }
    Message& lastMessage = getLastMessage();
    if (message == lastMessage.message) {
        ++lastMessage.count;
    } else {
        messages.emplace_back(message, type);
    }
}

void Console::render(sf::RenderWindow& window) {
    // Render console
    sf::Vector2u windowSize = window.getSize();
    sf::View uiView(sf::FloatRect(0.f, 0.f, windowSize.x, windowSize.y));
    window.setView(uiView);
    sf::RectangleShape consoleBackground;
    const int consoleMargin = 10;
    const int fontSize = 16;
    const auto spaceBetweenMessages = int(fontSize * 0.6);

    auto consoleWidthPixels = int(CONSOLE_WIDTH * windowSize.x);
    auto consoleStart = windowSize.x - consoleWidthPixels;
    auto consoleTextStart = consoleStart + consoleMargin;
    auto consoleTextWidth = consoleWidthPixels - (consoleMargin * 2);
    auto consoleBottom = windowSize.y - 100;

    // Draw console background
    consoleBackground.setPosition(consoleStart, 0.f);
    consoleBackground.setSize(sf::Vector2f(consoleWidthPixels, windowSize.y));
    consoleBackground.setFillColor(sf::Color::Black);
    window.draw(consoleBackground);

    // Position and draw console text
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(fontSize);
    auto charHeightPixels = font.getLineSpacing(fontSize);
    auto numMessages = messages.size();
    sf::FloatRect textBounds;
    sf::FloatRect lastTextBounds;
    int positionY = consoleBottom;
    int lastMessageLines = 0;
    for (int i = 1; i <= numMessages; ++i) {
        lastTextBounds = textBounds;
        auto message = numMessages - i;
        text.setString(getMessageString(message));
        text.setPosition(consoleTextStart, 0);
        wrapText(text, window.getSize().x - consoleMargin);
        auto formattedTextHeight = getNumLines(text) * charHeightPixels;
        text.setOrigin(0, formattedTextHeight);
        if (i == 1) {
            text.setPosition(consoleTextStart, consoleBottom);
        } else {
            auto lastMessageTop = lastTextBounds.top;
            text.setPosition(consoleTextStart, lastMessageTop - spaceBetweenMessages);
        }
        textBounds = text.getGlobalBounds();
        text.setFillColor(getMessageColor(getMessageType(message)));
        window.draw(text);
        if (textBounds.top < 0)
            return; // Stop drawing messages as soon as one goes off screen
    }
    //window.draw(consoleText);
}

wstring Console::getMessageString(int i) const {
    if (messages[i].count == 1) {
        return messages[i].message;
    } else {
        wstringstream message;
        message << messages[i].message;
        message << " (x" << messages[i].count << ")";
        return message.str();
    }
}

Console::Console() {
    if (!font.loadFromFile(fontsPath() + "/PxPlus_IBM_VGA8.ttf")) {
        cerr << "Could not load terminal font!" << endl;
    }
}

message_type Console::getMessageType(int i) const {
    return messages[i].type;
}

sf::Color Console::getMessageColor(message_type type) const {
    switch (type) {
        case info:
            return getColor(white);
        case warning:
        case serious:
            return getColor(light_red);
        case positive:
            return getColor(light_cyan);
        default:
            return getColor(gray);
    }
}

float Console::getNumLines(sf::Text& text) {
    string message = text.getString();
    int count = 1;
    for (auto c : message) {
        if (c == '\n')
            ++count;
    }
    return count;
}

void Console::wrapText(sf::Text &text, int rightBound) {
    size_t lastSpaceIndex = 0;
    float offset = 0.f;
    wstring message = text.getString();
    for (auto i = 0; i < message.length(); ++i) {
        if (message[i] == ' ') lastSpaceIndex = static_cast<size_t>(i);
        if (text.findCharacterPos(i).x - offset >= rightBound) {
            if (lastSpaceIndex != -1) {
                message[lastSpaceIndex] = '\n';
                offset = text.findCharacterPos(lastSpaceIndex).x - text.getPosition().x;
            }
        }
    }
    text.setString(message);
}

Message& Console::getLastMessage() {
    return messages[messages.size()-1];
}

sf::Color Console::getColor(vga_color color) const {
    return sf::Color(color);
}

