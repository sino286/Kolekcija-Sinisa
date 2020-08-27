#include "game.h"
#include "playstate.h"
#include "gamestate.h"

#include <iostream>

Game::Game(Game *pGame) : mWindow(sf::VideoMode(500,600), "Tetris"), mGameSpeed(3.0f),
               mGameScore(0)
{
    // Inicijalizacija stanja dolazi ovdje
    mAllStates[GameState::State::Playing] = new PlayState(pGame);
    mAllStates[GameState::State::Welcome] = new WelcomeState(pGame);
    mAllStates[GameState::State::Speed] = new SpeedState(pGame);

    mGameSpeed = 3.0f;
    mGameScore = 0;

    setState(GameState::State::Welcome);
}

Game::~Game()
{
   // Eventualna dealokacija
   for( auto x : mAllStates) delete x;
}

void Game::run(){
    while(mWindow.isOpen()){
        processEvents();
        update();
        render();
    }
}

void Game::setState(GameState::State st)
{
    mpGameState = mAllStates[st];
    mpGameState->start();
}

sf::RenderWindow * Game::getWindow()
{
    return &mWindow;
}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            mWindow.close();
        else if(event.type ==sf::Event::Resized){
            // Spriječi deformaciju objekata prilikom promjene veličine prozora
            sf::FloatRect viewRect(0, 0, event.size.width, event.size.height);
            mWindow.setView(sf::View(viewRect));
        }
        else {
            mpGameState->handleEvents(event);
		}
    }
}

void Game::update()
{
    mpGameState->update();
}

void Game::render()
{
     mWindow.clear();
     mpGameState->render();
     mWindow.display();
}
