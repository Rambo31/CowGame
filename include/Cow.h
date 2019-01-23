#ifndef COW_H
#define COW_H

#include<SFML/Graphics/Sprite.hpp>

#include<SFML/System/Time.hpp>

class Cow
{
    public:
                            Cow();
    void                    updateCowAnimation(sf::Time elapsedTime);
    public:
    sf::Sprite              mSprite;

    sf::Sprite              mEmptyBar;
    sf::Sprite              mHealth;

    sf::Sprite              mHunger;

    float                   mBaseHealth;
    float                   mCurHealth;

    float                   mBaseHunger;
    float                   mCurHunger;

    float                   curFrame;

    bool                    mIsGoingToEat;
    bool					mIsMovingUp;
    bool					mIsMovingDown;
    bool					mIsMovingRight;
    bool					mIsMovingLeft;
};

#endif // COW_H
