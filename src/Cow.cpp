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

void Cow::updateCowCollisionWithBarriers(bool isXDir, sf::IntRect bounds)
{
    if(isXDir)
    {
        if(mSprite.getGlobalBounds().left < 0)
        {
            mSprite.setPosition(0, mSprite.getPosition().y);
        }
        else if(mSprite.getGlobalBounds().left +
                mSprite.getGlobalBounds().width >
                bounds.width)
        {

            mSprite.setPosition(bounds.width -
                mSprite.getGlobalBounds().width,
                mSprite.getPosition().y);

        }
    }
    else
    {
        if(mSprite.getGlobalBounds().top < 32)
        {
            mSprite.setPosition(mSprite.getPosition().x, 32);
        }
        else if(mSprite.getGlobalBounds().top +
                mSprite.getGlobalBounds().height >
                bounds.height)
        {
            mSprite.setPosition(mSprite.getPosition().x,
                bounds.height -
                mSprite.getGlobalBounds().height);
        }
    }
}


void Cow::updateCowHealthHunger(sf::Time elapsedTime)
{
    if(mCurHunger >= 0)
    {
        mCurHunger -= 0.015f * elapsedTime.asMilliseconds();

        float hunger_val = mCurHunger / mBaseHunger;

        mHunger.setScale(hunger_val, 1);
    }
    else if(mCurHealth >= 0)
    {
        mCurHealth -= 0.008f * elapsedTime.asMilliseconds();

        float health_val = mCurHealth / mBaseHealth;

        mHealth.setScale(health_val, 1);
    }
}


void Cow::update(sf::Time elapsedTime, sf::IntRect bounds)
{
    updateCowHealthHunger(elapsedTime);

	updateCowAnimation(elapsedTime);

    updateCowCollisionWithBarriers(true, bounds);

	updateCowCollisionWithBarriers(false, bounds);
}

void Cow::aiBehavior()
{

}
