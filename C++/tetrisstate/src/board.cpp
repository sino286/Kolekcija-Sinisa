#include "board.h"

Board::Board(): mGrid(sf::Lines), mUniformDist(0,mPiece.SIZE - 1)
{
    mDx = mWidth / mCols;
    mDy = mHeight / mRows;

    mGrid.resize(2 * mCols + 2 * mRows + 4);
    int k = 0;
    for(int i = 0 ; i <= 2 * mRows ; i+=2){
        mGrid[k].position = sf::Vector2f(mLeftMargin, mTopMargin + i/2 * mDy);
        mGrid[k+1].position = sf::Vector2f(mLeftMargin + mWidth, mTopMargin + i/2*mDy);
        k+=2;
        }

    for(int i = 0 ; i <= 2 * mCols ; i+=2){
        mGrid[k].position = sf::Vector2f(mLeftMargin + i/2 * mDx , mTopMargin );
        mGrid[k+1].position = sf::Vector2f(mLeftMargin + i/2 * mDx, mTopMargin + mHeight);
        k+=2;
        }

    clearState();
}

Board::~Board()
{
}

void Board::update(bool leftPressed, bool rightPressed, bool upPressed, bool downPressed)
{
    if(mPiece.mClock.getElapsedTime() > sf::seconds(mDt)){
        mPiece.mClock.restart();

        if( !movePiece(1,0)){
            placePiece();
            mNoLinesCompleted += clearLines();
            if(checkSpace()){
                spawnPiece();
            } else {
                mGameOver = true;
            }

        }
    }

    if(downPressed) {
        while(movePiece(1,0));
    }

    if(upPressed) rotatePiece();
    if(leftPressed) movePiece(0,-1);
    if(rightPressed) movePiece(0,1);
}

void Board::spawnPiece()
{
    mPiece.mXposition = 0;
    mPiece.mYposition = (mCols / 2) - (mPiece.MAT_SIZE / 2);
    mPiece.mType = (Tetrimino::Types) mUniformDist(mRNE);
    mPiece.mRotacija = 0;
}

void Board::clearState()
{
    mRNE.seed(r());
    clearNoLinesCompleted();

    for(int i = 0 ; i < mRows ; ++i){
        for(int j = 0 ; j < mCols ; ++j){
            mGridContent[i][j] = EMPTY;
        }
    }
    mGameOver = false;
    spawnPiece();
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();


    for(int i = 0; i < mPiece.MAT_SIZE ; ++i) {
        for(int j = 0; j < mPiece.MAT_SIZE ; ++j){
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j] != 0){
                sf::RectangleShape rect;
                rect.setSize(sf::Vector2f(mDx, mDy));
                rect.setFillColor(mPiece.mColors[mPiece.mType]);
                rect.setPosition(mTopMargin + mPiece.mYposition * mDy + mDy * j, mLeftMargin + mPiece.mXposition * mDx  + mDx * i);
                target.draw(rect);
            }
        }
    }

    for(int i = 0; i < mRows; ++i){
        for(int j = 0; j < mCols; ++j){
            if(mGridContent[i][j] != EMPTY){
                sf::RectangleShape rect;
                rect.setSize(sf::Vector2f(mDx, mDy));
                rect.setFillColor(mPiece.mColors[mGridContent[i][j]]);
                rect.setPosition(mTopMargin + mDy * j, mLeftMargin + mDx * i);
                target.draw(rect);
             }

        }
    }

    target.draw(mGrid, states);

}

bool Board::checkSpace()
{
    for(int i = 0; i < mPiece.MAT_SIZE - 1 ; ++i) {
        for(int j = 0; j < mPiece.MAT_SIZE ; ++j){
                if(mGridContent[0 + i][(mCols / 2) - (mPiece.MAT_SIZE / 2) + j] != EMPTY){
                    return false;
                }
        }
    }
    return true;

}

void Board::placePiece()
{
    for(int i = 0; i < mPiece.MAT_SIZE ; ++i) {
        for(int j = 0; j < mPiece.MAT_SIZE ; ++j){
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j] != 0){
                mGridContent[mPiece.mXposition + i][mPiece.mYposition + j] = mPiece.mType;
            }
         }
    }

}

void Board::removePiece()
{

}

bool Board::movePiece(int x, int y)
{
    for(int i = 0; i < mPiece.MAT_SIZE ; ++i) {
        for(int j = 0; j < mPiece.MAT_SIZE ; ++j){
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j] != 0){
                if(mPiece.mYposition + j + y < 0 || mPiece.mYposition + j + y >= mCols)
                    return false;
                if(mPiece.mXposition + i + x >= mRows)
                    return false;
                if(mGridContent[mPiece.mXposition + i + x][mPiece.mYposition + j + y] != EMPTY){
                    return false;
                }
            }

        }
    }
    mPiece.move(x,y);
    return true;
}

bool Board::rotatePiece()
{
    for(int i = 0; i < mPiece.MAT_SIZE ; ++i) {
        for(int j = 0; j < mPiece.MAT_SIZE ; ++j){
            if(mPiece.mDijelovi[mPiece.mType][(mPiece.mRotacija + 1) % mPiece.N_ROTACIJA][i][j] != 0){
                if(mPiece.mYposition + j < 0 || mPiece.mYposition + j >= mCols)
                    return false;
                if(mPiece.mXposition + i >= mRows)
                    return false;
                if(mGridContent[mPiece.mXposition + i][mPiece.mYposition + j] != EMPTY){
                    return false;
                }
            }

        }
    }
    mPiece.rotate();
    return true;
}

bool Board::isLineFull(int y) const
{
     for(int i = 0; i < mCols; ++i){
        if(mGridContent[y][i] == EMPTY){

            return false;

        }
     }
     return true;
}

int Board::clearLines()
{
    int broj = 0;
    for(int i = 0; i < mRows; ++i){
        if(isLineFull(i)){
            broj+=1;
            for(int j = i; j > 1; --j){
                for(int k = 0; k < mCols; ++k){
                    mGridContent[j][k] = mGridContent[j-1][k];
                }
            }
        }
    }
    return broj;
}
