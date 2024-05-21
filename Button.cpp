#include "Button.h"

void Button::setButtonProperties(const string& text, const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size) {

    isPressed = false;
    actualPos = position;
    buttonShape.setPosition(position);
    buttonShape.setSize(size);
    buttonShape.setOutlineColor(sf::Color::Black);
    buttonShape.setOutlineThickness(2.0);

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(16);
    buttonText.setFillColor(sf::Color::Black);

    float xPos = (position.x + buttonShape.getGlobalBounds().width / 2) - (buttonText.getGlobalBounds().width / 2);
    float yPos = (position.y + buttonShape.getGlobalBounds().height / 2) - (buttonText.getGlobalBounds().height / 2);

    buttonText.setPosition({ xPos, yPos });
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(buttonShape);
    window.draw(buttonText);
}

bool Button::isMouseOver(sf::Vector2i mousePosition) {
    float mouseX = mousePosition.x;
    float mouseY = mousePosition.y;

    float buttonPosX = buttonShape.getPosition().x;
    float buttonPosY = buttonShape.getPosition().y;

    if (mouseX < buttonPosX + buttonShape.getLocalBounds().width && mouseX > buttonPosX &&
        mouseY < buttonPosY + buttonShape.getLocalBounds().height && mouseY > buttonPosY) {
        return true;
    }
    return false;
}

void Button::setPressed(bool pressed) {
    isPressed = pressed;
    buttonShape.setFillColor(pressed ? sf::Color::Blue : sf::Color::White);
}

bool Button::getPressedStatus() {
    return isPressed;
}

void Button::setText(const string& text) {
    buttonText.setString(text);
    float xPos = (actualPos.x + buttonShape.getGlobalBounds().width / 2) - (buttonText.getGlobalBounds().width / 2);
    float yPos = (actualPos.y + buttonShape.getGlobalBounds().height / 2) - (buttonText.getLocalBounds().height / 2);

    buttonText.setPosition({ xPos, yPos });
}

string Button::getText() const {
    return buttonText.getString();
}
