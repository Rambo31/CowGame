#include<cstdlib>
#include<ctime>

#include<SFML/Graphics/RectangleShape.hpp>

#include "GameState.h"
#include "StringHelpers.h"
#include"Utility.h"


const float GameState::PlayerSpeed = 100.f;

GameState::GameState(StateStack& my_stack, Context context)
: State(my_stack, context)
, mWindow(*context.window)
, mWorldBounds(0, 0, mWindow.getSize().x, mWindow.getSize().y)
, mCow(*context.player)
, mAICows(new Cow[2])
, mFlower()
, mFlowerGenTime()
, mMap(new sf::String[mWindow.getSize().y / 32])
, mScoreText()
, mScore(0)
, mWall()
, mTextureHolder(*context.textures)
, mFontHolder(*context.fonts)
{



    loadFonts();
    loadTextures();
    buildScene();

    sf::Font& sansat_font = mFontHolder.get(Fonts::Sansation);


	mScoreText.setFont(sansat_font);
	mScoreText.setPosition(mWindow.getSize().x / 2, 16);
	mScoreText.setCharacterSize(15);
}


bool GameState::handleEvent(const sf::Event& event)
{
    switch (event.type)
    {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;

        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;

        case sf::Event::Closed:
            mWindow.close();
            break;
		}

	return true;
}

bool GameState::update(sf::Time elapsedTime)
{
    mFlowerGenTime += elapsedTime;

    if(mFlowerGenTime.asSeconds() > 1.5f)
    {
        generateFlower();
        mFlowerGenTime -= sf::seconds(1.5f);
    }

	mScore += mCow.update(elapsedTime, mMap, mWorldBounds);

    for(int i = 0; i < 2; i++)
    {
        mAICows[i].update(elapsedTime, mMap, mWorldBounds);
    }


    return true;
}

void GameState::draw()
{
    sf::Color color(52, 171, 24);

	mWindow.clear(color);

	sf::RectangleShape top_rect(sf::Vector2f(mWindow.getSize().x, 64));
	top_rect.setFillColor(sf::Color::Black);
	mWindow.draw(top_rect);


    for(int i = 0; i < mWindow.getSize().y / 32; i++)
    {
        for(int j = 0; j < mWindow.getSize().x / 32; j++)
        {
            if(*(mMap[i].begin() + j) == '1')
            {
                mFlower.mSprite.setPosition(j * 32, i * 32);
                mWindow.draw(mFlower.mSprite);
            }
            else if(*(mMap[i].begin() + j) == '2')
            {
                mWall.setPosition(j * 32, i * 32);
                mWindow.draw(mWall);
            }
        }
    }

    mCow.mEmptyBar.setPosition(mWindow.getSize().x - mCow.mEmptyBar.getGlobalBounds().width, 0);
	mWindow.draw(mCow.mEmptyBar);
	mWindow.draw(mCow.mHealth);

	mCow.mEmptyBar.setPosition(mWindow.getSize().x - mCow.mEmptyBar.getGlobalBounds().width, 32);
    mWindow.draw(mCow.mEmptyBar);
    mWindow.draw(mCow.mHunger);

    for(int i = 0; i < 2; i++)
    {
     mWindow.draw(mAICows[i].mSprite);
    }

	mWindow.draw(mCow.mSprite);


	mScoreText.setString("Score = " + toString(mScore));

	centerOrigin(mScoreText);

	mWindow.draw(mScoreText);

}


void GameState::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mCow.mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mCow.mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mCow.mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mCow.mIsMovingRight = isPressed;
    else if (key == sf::Keyboard::Space)
        mCow.mIsGoingToEat = isPressed;
}



void GameState::buildScene()
{

    for(int i = 0; i < mWindow.getSize().y / 32; i++)
    {
        for(std::size_t j = 0; j < mWindow.getSize().x / 32; j++)
        {
            if(i == 1  || i == mWindow.getSize().y / 32 - 1)
            {
                mMap[i].insert(j, "2");
            }
            else
            {
                mMap[i].insert(j, "0");
            }

        }
    }


    sf::Texture& cow_texture = mTextureHolder.get(Textures::Cow);

    mCow.mSprite.setTexture(cow_texture);
	mCow.mSprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
	mCow.mSprite.setPosition(100.f, 100.f);

	mAICows[0].setType(Cow::CowType::AI_1);
    mAICows[0].mSprite.setTexture(cow_texture);
	mAICows[0].mSprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
	mAICows[0].mSprite.setPosition(0, 64.f);
	mAICows[0].mSprite.setColor(sf::Color(237, 206, 206));


    mAICows[1].setType(Cow::CowType::AI_2);
    mAICows[1].mSprite.setTexture(cow_texture);
	mAICows[1].mSprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
	mAICows[1].mSprite.setPosition(224.f, 224.f);
	mAICows[1].mSprite.setColor(sf::Color(237, 206, 206));


	sf::Texture& health_hunger_tex =  mTextureHolder.get(Textures::HealthHunger);
	mCow.mEmptyBar.setTexture(health_hunger_tex);
	mCow.mEmptyBar.setTextureRect(sf::IntRect(0, 0, 128, 32));


    mCow.mHealth.setTexture(health_hunger_tex);
    mCow.mHealth.setTextureRect(sf::IntRect(0, 32, 128, 32));
    mCow.mHealth.setPosition(mWindow.getSize().x - mCow.mHealth.getGlobalBounds().width, 0);


    mCow.mHunger.setTexture(health_hunger_tex);
    mCow.mHunger.setTextureRect(sf::IntRect(0, 64, 128, 32));
    mCow.mHunger.setPosition(mWindow.getSize().x - mCow.mHunger.getGlobalBounds().width, 32);


	sf::Texture& flower_tex = mTextureHolder.get(Textures::Flower);
    mFlower.mSprite.setTexture(flower_tex);
    mFlower.mSprite.setTextureRect(sf::IntRect(64, 64, 32, 32));

    for(int i = 0; i < 3; i++)
        generateFlower();

    sf::Texture& walls = mTextureHolder.get(Textures::Walls);
    mWall.setTexture(walls);
    mWall.setTextureRect(sf::IntRect(192, 128, 32, 32));


}

void GameState::loadTextures()
{
    mTextureHolder.load(Textures::Cow, "images/cow.png");
    mTextureHolder.load(Textures::Flower, "images/flower.png");
    mTextureHolder.load(Textures::HealthHunger, "images/SleekBars.png");
    mTextureHolder.load(Textures::Walls, "images/walls.png");
}

void GameState::generateFlower()
{
    static unsigned int seed = 0;

    srand(time(0) + seed++);


    int x_pos = rand() % (mWindow.getSize().x / 32);
    int y_pos = 2 + rand() % (mWindow.getSize().y / 32 - 2);


    if(*(mMap[y_pos].begin() + x_pos) != '1' && *(mMap[y_pos].begin() + x_pos) != '2')
    {
        mMap[y_pos].erase(x_pos);
        mMap[y_pos].insert(x_pos, "1");
    }
}


void GameState::loadFonts()
{
   // mFontHolder.load(Fonts::Sansation, "fonts/Sansation.ttf");
}


GameState::~GameState()
{
    delete mMap;
    delete mAICows;
}
