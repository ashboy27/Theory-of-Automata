#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Dictionary.h"
#include "Button.h"

class TextEditor {
public:
    TextEditor(Dictionary& dict);
    void run();

private:
    void handleEvents();
    void handleTextInput(sf::Uint32 unicode);
    void handleKeyPress(sf::Keyboard::Key key);
    void handleMouseClick(int mouseX, int mouseY);
    void autoCorrect();
    void update();
    void replaceCurrentWord(const std::string& newWord); // New method

    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;
    sf::Text suggestionLabel; // Text label for suggestions
    sf::RectangleShape cursor;
    sf::Clock clock;
    bool isBlinking = false;

    Dictionary& dictionary;
    std::vector<std::string> lines;
    int currentLineIndex = 0;
    int cursorPosition = 0;

    Button autoCorrectButton;
    Button clearAllButton; // Added clear all button
    Button suggestionButton1;
    Button suggestionButton2;
    Button suggestionButton3;
};

#endif // TEXTEDITOR_H
