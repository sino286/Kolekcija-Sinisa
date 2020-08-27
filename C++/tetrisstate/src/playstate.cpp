#include "playstate.h"
#include "game.h"

PlayState::PlayState(Game *pGame): GameState(pGame)
{
}

void PlayState::start()
{
    mBoard.setSpeed(mpGame->mGameSpeed);
    mScore.resetScore();
    mBoard.clearState();
}

void PlayState::handleEvents(sf::Event event)
{
        switch(event.type)
        {
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Up)
                mBoard.update(false,false,true,false);
            if(event.key.code == sf::Keyboard::Space)
                mBoard.update(false, false, false, true);
            if(event.key.code == sf::Keyboard::Left)
                mBoard.update(true, false, false, false);
            if(event.key.code == sf::Keyboard::Right)
                mBoard.update(false, true, false, false);

            break;
        }
}

void PlayState::update()
{
    mBoard.update(false, false, false, false);
    if(mBoard.getNoLinesCompleted() > 0){
        mScore.addNoLinesCompleted(mBoard.getNoLinesCompleted());
        mBoard.clearNoLinesCompleted();
    }
    mScore.update();
    if(mBoard.isGameOver()){
        mpGame->mGameScore = mScore.getScore();
        mpGame->setState(GameState::State::Speed);

    }
}

void PlayState::render()
{
    mpGame->getWindow()->draw(mBoard);
    mpGame->getWindow()->draw(mScore);
}
