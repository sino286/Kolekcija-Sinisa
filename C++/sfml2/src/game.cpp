#include "game.h"
#include <algorithm>
#include <vector>

// Ovdje dolazi vaš kod

Game::Game(float Dx, float Dy, int bKugli, float radius ) : mWindow(sf::VideoMode(Dx + 100, Dy + 100), "Odbijajuce kuglice")
{
    mDx = Dx;
    mDy = Dy;
    mRectangle.setSize(sf::Vector2f(mDx,mDy));
    mRectangle.setFillColor(sf::Color::Black);
    mRectangle.setOutlineThickness(5.0f);
    mRectangle.setOutlineColor(sf::Color::Red);
    mRectangle.setPosition(50,50);



    char c = 'A';
    for(int i = 0 ; i < bKugli ; ++i){

        mBall.push_back(std::unique_ptr<Ball>(new Ball()));
        mBall[i]->setRadius(radius);
        mBall[i]->setChar(c);
        ++c;
    }
    initPositions(bKugli, radius);
    initVelocity(90.0);
}

void Game::run()
{
    sf::Time dt = sf::seconds(1.0f / 60);
    sf::Time protekloVrijeme = sf::Time::Zero;
    sf::Clock clock;
    while(mWindow.isOpen()){
        processEvents();
        protekloVrijeme += clock.restart();
        while(protekloVrijeme >= dt){
                  protekloVrijeme -= dt;
                  update(dt);
        }
        render();
    }

}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event)){
        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Game::update(sf::Time dt)
{
    float rotacija = 2 * dt.asSeconds(); //2 stupnja u sekundi

    for(auto &b : mBall){
        checkForCollisionsWithBalls(&*b, dt);
        checkForCollisionsWithWalls(&*b, dt);
        b->rotate(rotacija);
        b->move(b->mVelocity * dt.asSeconds());
    }

}

void Game::render()
{
    mWindow.clear();

    mWindow.draw(mRectangle);

    for(auto &b : mBall)
        mWindow.draw(*b);

    mWindow.display();
}

void Game::initPositions(std::size_t nBalls, float radius)
{
    std::random_device rd;
    mRand.seed(rd());
    std::vector<sf::Vector2f> pozicije;
    std::vector<int> pozicijeX ((int) (mDx / (2*radius + 5))-1);
    std::vector<int> pozicijeY ((int) (mDy / (2*radius + 5))-1);

    std::iota(pozicijeX.begin(), pozicijeX.end(), 1 );
    std::iota(pozicijeY.begin(), pozicijeY.end(), 1 );

    for(auto i : pozicijeX){
        for(auto j : pozicijeY){
            pozicije.push_back(sf::Vector2f(50 + i* (2*radius+5), 50 + j * (2*radius+5)));
        }
    }
    std::shuffle(pozicije.begin(), pozicije.end(), mRand);

    std::vector<sf::Vector2f>::iterator it = pozicije.begin();

    for(auto &b : mBall){      
        b->setPosition(*it);
        ++it;
        if(it == pozicije.end()) break;
    }


}

void Game::initVelocity(float maxVel)
{
    std::random_device rd;
    mRand.seed(rd());
    std::normal_distribution<float> d(maxVel,120.0); // median maxValue, standardna devijacija 120
    for(auto &b : mBall){
        b->mVelocity.x = d(mRand);
        b->mVelocity.y = d(mRand);
    }

}

void Game::checkForCollisionsWithWalls(Ball *pball, sf::Time dt) const
{
    auto bPos = pball->getPosition();
    auto r = pball ->getRadius();
    auto rPos = mRectangle.getPosition();

    if (bPos.x - r + (pball->mVelocity.x * dt.asSeconds()) <  rPos.x )
        pball->mVelocity.x *= -1;

    if (bPos.y - r + (pball->mVelocity.y * dt.asSeconds()) <  rPos.y )
        pball->mVelocity.y *= -1;

    if (bPos.x + r + (pball->mVelocity.x * dt.asSeconds()) > rPos.x + mDx )
        pball->mVelocity.x *= -1;

    if (bPos.y + r + (pball->mVelocity.y * dt.asSeconds()) > rPos.y + mDy )
        pball->mVelocity.y *= -1;

}

void Game::checkForCollisionsWithBalls(Ball *pball, sf::Time dt) const
{
    auto b1Pos = pball->getPosition();
    auto r = pball ->getRadius();
    float udaljenost, bUdaljenost;
    float d1, d2, bd1, bd2;


    for(auto &b : mBall){
        if (&*b == pball) continue;
        else{
            auto b2Pos = (*b).getPosition();
            d1 = (b1Pos.x - b2Pos.x);
            d2 = (b1Pos.y - b2Pos.y);
            udaljenost = (d1*d1 + d2*d2); //trenutna udaljenost
            bd1 = (b1Pos.x + (pball->mVelocity.x * dt.asSeconds()) - (b2Pos.x + ((*b).mVelocity.x) * dt.asSeconds()));
            bd2 = (b1Pos.y + (pball->mVelocity.y * dt.asSeconds()) - (b2Pos.y + ((*b).mVelocity.y) * dt.asSeconds()));
            bUdaljenost = (bd1*bd1 + bd2*bd2); //buduca udaljenost
            if ( udaljenost < 4*r*r && udaljenost > bUdaljenost ){
                std::swap(pball->mVelocity,(*b).mVelocity );
            }
        }

    }
}
