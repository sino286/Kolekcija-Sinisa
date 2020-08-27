#include "score.h"
#include <cstdlib>
#include <iostream>

Score::Score()
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }
    mScoreText.setFont(mFont);
    mScoreText.setCharacterSize(64);
    mScoreText.setStyle(sf::Text::Bold);
    mScoreText.setPosition(sf::Vector2f(300,50));


}

void Score::addNoLinesCompleted(int n)
{
  mScore += n * 10;

}

void Score::setGameOver()
{
  mGameOverText.setFont(mFont);
  mGameOverText.setCharacterSize(32);
  mGameOverText.setStyle(sf::Text::Bold);
  mGameOverText.setString("GAME OVER!");
  mGameOverText.setPosition(sf::Vector2f(300,150));
}

void Score::update()
{
  mScoreText.setString(std::to_string(mScore));
}

void Score::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mScoreText);
    target.draw(mGameOverText);
}
