#include "TextEditor.h"

TextEditor::TextEditor(Dictionary& dict) : window(sf::VideoMode::getFullscreenModes()[0], "SFML Text Editor"), dictionary(dict) {

    if (!font.loadFromFile("OpenSans-Light.ttf")) {
        cerr << "Error loading font\n";
        exit(1);
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);

    cursor.setSize(sf::Vector2f(2, text.getCharacterSize()));
    cursor.setFillColor(sf::Color::White);

    // Initialize the first line
    lines.emplace_back("");

    autoCorrectButton.setButtonProperties("Auto Correct", font, sf::Vector2f(900, 0), sf::Vector2f(100, 50));
    clearAllButton.setButtonProperties("Clear All", font, sf::Vector2f(900, 60), sf::Vector2f(100, 50));
    suggestionButton1.setButtonProperties("", font, sf::Vector2f(100, 550), sf::Vector2f(200, 50)); // Position for suggestionButton1
    suggestionButton2.setButtonProperties("", font, sf::Vector2f(350, 550), sf::Vector2f(200, 50)); // Position for suggestionButton2
    suggestionButton3.setButtonProperties("", font, sf::Vector2f(600, 550), sf::Vector2f(200, 50));

  
    suggestionLabel.setFont(font);
    suggestionLabel.setString("SUGGESTIONS");
    suggestionLabel.setCharacterSize(24);
    suggestionLabel.setFillColor(sf::Color::White);
    suggestionLabel.setPosition(100, 510);
}

void TextEditor::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
    }
}

void TextEditor::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::TextEntered) {
            handleTextInput(event.text.unicode);
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == 27)
                window.close();
            else 
            handleKeyPress(event.key.code);
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            handleMouseClick(event.mouseButton.x, event.mouseButton.y);
        }
    }
}

void TextEditor::handleTextInput(sf::Uint32 unicode) {

    if (unicode == 8) { // Backspace
        if (cursorPosition > 0) {
            lines[currentLineIndex].erase(cursorPosition - 1, 1);
            cursorPosition--;
        }
        else if (cursorPosition == 0 && currentLineIndex > 0) {
            // Merge with previous line
            cursorPosition = lines[currentLineIndex - 1].size();
            lines[currentLineIndex - 1] += lines[currentLineIndex];
            lines.erase(lines.begin() + currentLineIndex);
            currentLineIndex--;
        }
    }
    else if (unicode == 13) { // Enter
        string newLine = lines[currentLineIndex].substr(cursorPosition);
        lines[currentLineIndex].erase(cursorPosition);
        lines.insert(lines.begin() + currentLineIndex + 1, newLine);
        currentLineIndex++;
        cursorPosition = 0;
    }
    else if (unicode < 128) { // ASCII characters
        lines[currentLineIndex].insert(cursorPosition, 1, static_cast<char>(unicode));
        cursorPosition++;
    }
}

void TextEditor::handleKeyPress(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Left) {
        if (cursorPosition > 0) {
            cursorPosition--;
        }
        else if (cursorPosition == 0 && currentLineIndex > 0) {
            currentLineIndex--;
            cursorPosition = lines[currentLineIndex].size();
        }
    }
    else if (key == sf::Keyboard::Right) {
        if (cursorPosition < lines[currentLineIndex].size()) {
            cursorPosition++;
        }
        else if (cursorPosition == lines[currentLineIndex].size() && currentLineIndex < lines.size() - 1) {
            currentLineIndex++;
            cursorPosition = 0;
        }
    }
    else if (key == sf::Keyboard::Up) {
        if (currentLineIndex > 0) {
            currentLineIndex--;
            cursorPosition = cursorPosition < lines[currentLineIndex].size() ? cursorPosition : lines[currentLineIndex].size();
        }
    }
    else if (key == sf::Keyboard::Down) {
        if (currentLineIndex < lines.size() - 1) {
            currentLineIndex++;
            cursorPosition = cursorPosition < lines[currentLineIndex].size() ? cursorPosition : lines[currentLineIndex].size();
        }
    }
}

void TextEditor::handleMouseClick(int mouseX, int mouseY) {
    if (autoCorrectButton.isMouseOver(sf::Vector2i(mouseX, mouseY))) {
        autoCorrectButton.setPressed(true);
        autoCorrect();
        autoCorrectButton.setPressed(false);
    }
    else if (clearAllButton.isMouseOver(sf::Vector2i(mouseX, mouseY))) {
        clearAllButton.setPressed(true);
        lines.clear();
        suggestionButton1.setText("");
        suggestionButton2.setText("");
        suggestionButton3.setText("");
        lines.emplace_back("");
        currentLineIndex = 0;
        cursorPosition = 0;
        clearAllButton.setPressed(false);

    }
    else if (suggestionButton1.isMouseOver(sf::Vector2i(mouseX, mouseY))) {
        replaceCurrentWord(suggestionButton1.getText());
    }
    else if (suggestionButton2.isMouseOver(sf::Vector2i(mouseX, mouseY))) {
        replaceCurrentWord(suggestionButton2.getText());
    }
    else if (suggestionButton3.isMouseOver(sf::Vector2i(mouseX, mouseY))) {
        replaceCurrentWord(suggestionButton3.getText());
    }
    else {
        autoCorrectButton.setPressed(false);
        clearAllButton.setPressed(false);
        // Calculate the line index based on the mouse y position
        int lineHeight = text.getCharacterSize() * 1.2f;
        currentLineIndex = (mouseY - 10) / lineHeight;
        if (currentLineIndex >= lines.size()) {
            currentLineIndex = lines.size() - 1;
        }

        // Calculate the cursor position within the line
        string currentLineText = lines[currentLineIndex];
        cursorPosition = 0;
        float offsetX = 10;

        for (int i = 0; i < currentLineText.size(); ++i) {
            sf::Text tempText(currentLineText.substr(0, i + 1), font, 24);
            if (offsetX + tempText.getLocalBounds().width >= mouseX) {
                break;
            }
            cursorPosition++;
        }
    }
}

void TextEditor::autoCorrect() {
    for (int i = 0; i < lines.size(); ++i) {
        istringstream lineStream(lines[i]);
        string word;
        string correctedLine;
        while (lineStream >> word) {
            vector<string> closestWords = dictionary.getWordRecommendation(word);

            if (!dictionary.spellCheck(word)) {
                string correctedWord = closestWords[0];
                correctedLine += correctedWord + " ";
                // Adjust cursor position if the corrected word is longer than the original word
                cursorPosition += correctedWord.size() - word.size();
            }
            else {
                correctedLine += word + " ";
            }
        }
        lines[i] = correctedLine;
    }
}


void TextEditor::update() {
    stringstream ss;
    vector<sf::Text> textSegments;

    for (int i = 0; i < lines.size(); ++i) {
        istringstream lineStream(lines[i]);
        string word;
        float lineOffsetY = text.getCharacterSize() * 1.2f * i;
        float offsetX = 10;

        while (lineStream >> word) {

            string temp = word;
            transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return tolower(c); });//conver to lower case to check

            vector<string> wordSuggestion = dictionary.getWordRecommendation(word);
            suggestionButton1.setText(wordSuggestion[0]);
            suggestionButton2.setText(wordSuggestion[1]);
            suggestionButton3.setText(wordSuggestion[2]);
            sf::Text wordText(temp + " ", font, 24);
            if (word.back() == '.' || word.back() == '?') {
                word.pop_back();
            }
            if (!autoCorrectButton.getPressedStatus() && !dictionary.spellCheck(word)) {
                wordText.setFillColor(sf::Color::Red);
            }
            else {
                wordText.setFillColor(sf::Color::White);
            }
            wordText.setPosition(offsetX, 10 + lineOffsetY);
            offsetX += wordText.getLocalBounds().width;
            textSegments.push_back(wordText);
        }
    }

    if (clock.getElapsedTime().asSeconds() > 0.1f) {
        isBlinking = !isBlinking;
        clock.restart();
    }

    string currentLineText = lines[currentLineIndex].substr(0, cursorPosition);
    sf::Text tempText(currentLineText, font, 24);
    float cursorX = tempText.getLocalBounds().width + 10;
    float cursorY = 10 + (currentLineIndex * text.getCharacterSize() * 1.2f);
    cursor.setPosition(cursorX, cursorY);

    window.clear();
    for (const auto& segment : textSegments) {
        window.draw(segment);
    }

    autoCorrectButton.draw(window);
    clearAllButton.draw(window); // Draw clear all button
    window.draw(suggestionLabel); // Draw suggestion label
    suggestionButton1.draw(window);
    suggestionButton2.draw(window);
    suggestionButton3.draw(window);
    if (isBlinking) {
        window.draw(cursor);
    }
    window.display();
}

void TextEditor::replaceCurrentWord(const string& newWord) {

    string& currentLine = lines[currentLineIndex];
    string beforeCursor = currentLine.substr(0, cursorPosition);
    string afterCursor = currentLine.substr(cursorPosition);

    size_t wordStart = beforeCursor.find_last_of(" \n");
    wordStart = (wordStart == string::npos) ? 0 : wordStart + 1;
    size_t wordEnd = afterCursor.find_first_of(" \n");
    wordEnd = (wordEnd == string::npos) ? currentLine.size() : cursorPosition + wordEnd;

    currentLine.replace(wordStart, wordEnd - wordStart, newWord);
    cursorPosition = wordStart + newWord.size();

}
