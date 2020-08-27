#include "game.h"

// Ovdje dolazi vaš kod.

Ball::Ball()
{
    mCircle.setFillColor(sf::Color::Green);

    if(!mFont.loadFromFile("Comfortaa-Bold.ttf"))
          throw std::runtime_error("Font");
    mText.setFont(mFont);
    mText.setCharacterSize(32);   
}

void Ball::setRadius(float r)
{
    mRadius = r;
    mCircle.setRadius(r);
    auto rect = mCircle.getLocalBounds();
    mCircle.setOrigin(rect.width / 2, rect.height / 2);
}

void Ball::setChar(char c)
{
    mChar = c;
    mText.setString(mChar);
    auto rect = mText.getLocalBounds();
    mText.setOrigin(rect.left + rect.width / 2.0f, rect.top  + rect.height / 2.0f);
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mCircle, states);
    target.draw(mText, states);


}
