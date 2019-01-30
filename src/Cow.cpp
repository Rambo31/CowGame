#include "Cow.h"

Cow::Cow(CowType type)
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
, mTime()
, mType(type)
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
                bounds.height - 32)
        {
            mSprite.setPosition(mSprite.getPosition().x,
                bounds.height - 32 - mSprite.getGlobalBounds().height);
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


unsigned int Cow::update(sf::Time elapsedTime,sf::String* my_map, sf::IntRect bounds)
{
    if(mType == CowType::AI)
    {
        aiBehavior_1(elapsedTime);
    }

    unsigned int score_value;

    score_value = updateCowCollisionWithEatable(my_map);

    updateCowMovement(elapsedTime);

    updateCowHealthHunger(elapsedTime);

	updateCowAnimation(elapsedTime);

    updateCowCollisionWithBarriers(true, bounds);

	updateCowCollisionWithBarriers(false, bounds);

	return score_value;
}

void Cow::aiBehavior_1(sf::Time elapsedTime)
{
    mTime += elapsedTime;


    if(mTime.asSeconds() > 25.f)
    {
        mTime -= sf::seconds(25.f);
    }

    if(mTime.asSeconds() < 3.5f)
    {
        mIsMovingLeft = false;
        mIsMovingDown = true;
    }
    else if (mTime.asSeconds() < 6.f)
    {
        mIsMovingDown = false;
        mIsMovingRight = true;
    }
    else if(mTime.asSeconds() < 9.5f)
    {
        mIsMovingUp = true;
    }
    else if(mTime.asSeconds() < 12.5f)
    {
        mIsMovingUp = false;
    }
    else if(mTime.asSeconds() < 16.f)
    {
        mIsMovingRight = false;
        mIsMovingDown = true;
    }
    else if(mTime.asSeconds() < 18.5f)
    {
        mIsMovingDown = false;
        mIsMovingLeft = true;
    }
    else if(mTime.asSeconds() < 22.f)
    {
        mIsMovingUp = true;
    }
    else if(mTime.asSeconds() < 25.f)
    {
        mIsMovingUp = false;
    }

}

unsigned int Cow::updateCowCollisionWithEatable(sf::String* mMap)
{
    if(mIsGoingToEat)
    {
        unsigned int sum = 0;

        for(int i = mSprite.getGlobalBounds().left / 32;
        i < (mSprite.getGlobalBounds().left + mSprite.getGlobalBounds().width) / 32;
        i++)
        {
            for(int j = mSprite.getGlobalBounds().top / 32;
            j < (mSprite.getGlobalBounds().top + mSprite.getGlobalBounds().height) / 32;
            j++)
            {
                if(*(mMap[j].begin() + i) == '1')
                {
                    mMap[j].erase(i);
                    mMap[j].insert(i, '0');

                    if(mCurHunger <= 70.f)
                    {
                        mCurHunger += 30.f;
                    }
                    else
                    {
                        mCurHunger = 100.f;
                    }

                    sum += 2;
                }
            }
        }

        return sum;
    }
    else
    {
        return 0;
    }
}

void Cow::updateCowMovement(sf::Time elapsedTime)
{
    float PlayerSpeed = 100.f;

    sf::Vector2f movement(0.f, 0.f);



	if (mIsMovingUp)
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;

    mSprite.move(movement * elapsedTime.asSeconds());
}
