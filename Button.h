#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
using namespace std;

class Button {
public:
    void setButtonProperties(const string& text, const sf::Font& font, const sf::Vector2f&,const sf::Vector2f&);
    void draw(sf::RenderWindow& window);
    bool isMouseOver(sf::Vector2i mousePosition);
    void setPressed(bool pressed);
    bool getPressedStatus();
    void setText(const std::string& text);
    std::string getText() const;

private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    bool isPressed;
    sf::Vector2f actualPos; // Track the actual position
};

#endif // BUTTON_H
