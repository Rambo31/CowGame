#ifndef COW_H
#define COW_H

#include<SFML/Graphics/Sprite.hpp>

class Cow
{
    public:
        Cow();
    public:
    sf::Sprite mSprite;

    sf::Sprite mEmptyBar;
    sf::Sprite mHealth;

    sf::Sprite mHunger;

    float mBaseHealth;
    float mCurHealth;

    float mBaseHunger;
    float mCurHunger;
};

#endif // COW_H
