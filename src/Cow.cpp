#include "Cow.h"

Cow::Cow()
: mBaseHealth(100.f)
, mCurHealth(100.f)
, mBaseHunger(100.f)
, mCurHunger(100.f)
, mSprite()
, mEmptyBar()
, mHealth()
, mHunger()
, mIsMovingUp(false)
, mIsMovingDown(false)
, mIsMovingRight(false)
, mIsMovingLeft(false)
, mIsGoingToEat(false)
, curFrame(0)
{
    //ctor
}


void Cow::updateCowAnimation(sf::Time elapsedTime)
{
    curFrame = curFrame + elapsedTime.asMilliseconds() * 0.01f;

    if((int)curFrame > 3)
    {
        curFrame-= 3;
    }

    if(mIsMovingUp)
    {
        mSprite.setTextureRect(sf::IntRect((int)curFrame * 128, 0, 128, 128));
    }
    else if(mIsMovingLeft)
    {
        mSprite.setTextureRect(sf::IntRect((int)curFrame * 128, 128, 128, 128));
    }
    else if(mIsMovingDown)
    {
        mSprite.setTextureRect(sf::IntRect((int)curFrame * 128, 256, 128, 128));
    }
    else if(mIsMovingRight)
    {
        mSprite.setTextureRect(sf::IntRect((int)curFrame * 128, 384, 128, 128));
    }

}
