#include "game.h"

Game::Game() : mWindow(sf::VideoMode(500,600), "Tetris")
{
    // Vaš kod dolazi ovdje (ako bude potrebe).   
}

void Game::run(){
    while(mWindow.isOpen()){
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            mWindow.close();
            break;

        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Up)
                mBoard.update(1);
            if(event.key.code == sf::Keyboard::Space)
                mBoard.update(2);
            if(event.key.code == sf::Keyboard::Left)
                mBoard.update(3);
            if(event.key.code == sf::Keyboard::Right)
                mBoard.update(4);

            break;
        case sf::Event::Resized:
            // Spriječi deformaciju objekata prilikom promjene veličine prozora
            sf::FloatRect viewRect(0, 0, event.size.width, event.size.height);
            mWindow.setView(sf::View(viewRect));
            break;
        }
    }
}

void Game::update()
{
   // Updatiranje scene. Vaš kod dolazi ovdje


    mBoard.update(0);
    if(mBoard.getNoLinesCompleted() > 0)
        mScore.addNoLinesCompleted(mBoard.getNoLinesCompleted());
        mBoard.clearNoLinesCompleted();
    mScore.update();
    if(mBoard.isGameOver())
        mScore.setGameOver();
}

void Game::render()
{
     mWindow.clear();


     mWindow.draw(mBoard);
     mWindow.draw(mScore);

     mWindow.display();
}
