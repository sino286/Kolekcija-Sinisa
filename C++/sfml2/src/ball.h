#pragma once
#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable, public sf::Transformable {
public:
    Ball();
    sf::Vector2f mVelocity;
    void setRadius(float r);
    void setChar(char c);
    float getRadius() const { return mRadius; }
private:
    sf::CircleShape mCircle;
    sf::Font mFont;
    sf::Text mText;
    float mRadius;
    char mChar;

    void draw (sf::RenderTarget &target, sf::RenderStates states) const override;
};





