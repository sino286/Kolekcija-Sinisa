#include "gamestate.h"
#include "game.h"
#include <cstdlib>
#include <iostream>

// Vaš kod dolazi ovdje.

WelcomeState::WelcomeState(Game *pGame) : GameState(pGame)
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }
    mText1.setFont(mFont);
    mText1.setCharacterSize(46);
    mText1.setStyle(sf::Text::Bold);
    mText1.setPosition(sf::Vector2f(30,100));
    mText1.setString("Tetris clone by S.Novak");

    mText2.setFont(mFont);
    mText2.setCharacterSize(32);
    mText2.setStyle(sf::Text::Italic);
    mText2.setPosition(sf::Vector2f(80,150));
    mText2.setString("Press any key to continue");
}

void WelcomeState::handleEvents(sf::Event event)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
        mpGame->setState(GameState::State::Playing);
        break;
    }
}

void WelcomeState::update()
{
}

void WelcomeState::render()
{
    mpGame->getWindow()->draw(mText1);
    mpGame->getWindow()->draw(mText2);
}

//Speedstate

SpeedState::SpeedState(Game *pGame) : GameState(pGame)
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }
    mText0.setFont(mFont);
    mText0.setCharacterSize(46);
    mText0.setStyle(sf::Text::Bold);
    mText0.setPosition(sf::Vector2f(50,100));

    mText1.setFont(mFont);
    mText1.setCharacterSize(42);
    mText1.setStyle(sf::Text::Bold);
    mText1.setPosition(sf::Vector2f(50,150));

    mText2.setFont(mFont);
    mText2.setCharacterSize(26);
    mText2.setStyle(sf::Text::Italic);
    mText2.setPosition(sf::Vector2f(20,250));
    mText2.setString("Use keys up and down to change the speed");

    mText3.setFont(mFont);
    mText3.setCharacterSize(26);
    mText3.setStyle(sf::Text::Italic);
    mText3.setPosition(sf::Vector2f(20,290));
    mText3.setString("Enter to continue");
}

void SpeedState::handleEvents(sf::Event event)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Up){
            if(mpGame->mGameSpeed < 50.0f)
                mpGame->mGameSpeed += 1.0f;
        }
        if(event.key.code == sf::Keyboard::Down){
            if(mpGame->mGameSpeed > 1.0f)
                mpGame->mGameSpeed -= 1.0f;
        }
        if(event.key.code == sf::Keyboard::Return)
            mpGame->setState(GameState::State::Playing);
        break;
    }
}

void SpeedState::update()
{
    mText0.setString("Score : " + std::to_string(mpGame->mGameScore));
    mText1.setString("Current speed : " + std::to_string(mpGame->mGameSpeed));
}

void SpeedState::render()
{
    mpGame->getWindow()->draw(mText0);
    mpGame->getWindow()->draw(mText1);
    mpGame->getWindow()->draw(mText2);
    mpGame->getWindow()->draw(mText3);
}
