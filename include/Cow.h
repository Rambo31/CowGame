#ifndef COW_H
#define COW_H

#include<SFML/Graphics/Sprite.hpp>

#include<SFML/System/Time.hpp>
#include<SFML/System/String.hpp>

class Cow
{
    public:
        enum CowType
        {
            Player,
            AI
        };

    public:
                            Cow(CowType type);
    void                    updateCowMovement(sf::Time elapsedTime);
    void                    updateCowCollisionWithEatable(sf::String* my_map);
    void                    updateCowAnimation(sf::Time elapsedTime);
    void                    updateCowCollisionWithBarriers(bool isXDir, sf::IntRect bounds);
    void                    updateCowHealthHunger(sf::Time elapsedTime);

    void                    update(sf::Time elapsedTime, sf::String* my_map, sf::IntRect bounds);
    void                    aiBehavior(sf::Time elapsed_time);

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

    sf::Time                mTime;
    CowType                 mType;

};

#endif // COW_H
