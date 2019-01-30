#include<cstdlib>
#include<ctime>

#include<SFML/Graphics/RectangleShape.hpp>

#include "Game.h"
#include "StringHelpers.h"


const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game()
: mWindow(sf::VideoMode().getFullscreenModes()[0], "SFML Application", sf::Style::Fullscreen)
, mWorldBounds(0, 0, mWindow.getSize().x, mWindow.getSize().y)
, mCow(Cow::CowType::Player)
, mAICow(Cow::CowType::AI)
, mFlower()
, mFlowerGenTime()
, mFont()
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
, mMap(new sf::String[mWindow.getSize().y / 32])
, mScoreText()
, mScore(0)
, mWall()
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

    loadTextures();
    buildScene();


	mFont.loadFromFile("fonts/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(0.f, 0.f);
	mStatisticsText.setCharacterSize(13);

	mScoreText.setFont(mFont);
	mScoreText.setPosition(mWindow.getSize().x / 2, 0);
	mScoreText.setCharacterSize(15);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
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
	}
}

void Game::update(sf::Time elapsedTime)
{
    mFlowerGenTime += elapsedTime;

    if(mFlowerGenTime.asSeconds() > 5.f)
    {
        generateFlower();
        mFlowerGenTime -= sf::seconds(5.f);
    }

	mScore += mCow.update(elapsedTime, mMap, mWorldBounds);

	mAICow.update(elapsedTime, mMap, mWorldBounds);
}

void Game::render()
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

    mWindow.draw(mAICow.mSprite);

	mWindow.draw(mCow.mSprite);


	mScoreText.setString("Score = " + toString(mScore));

	mWindow.draw(mScoreText);
	mWindow.draw(mStatisticsText);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
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



void Game::buildScene()
{

    sf::Texture& cow_texture = mTextureHolder.get(Textures::Cow);

    mCow.mSprite.setTexture(cow_texture);
	mCow.mSprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
	mCow.mSprite.setPosition(100.f, 100.f);

    mAICow.mSprite.setTexture(cow_texture);
	mAICow.mSprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
	mAICow.mSprite.setPosition(0, 64.f);
	mAICow.mSprite.setColor(sf::Color(237, 206, 206));

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

void Game::loadTextures()
{
    mTextureHolder.load(Textures::Cow, "images/cow.png");
    mTextureHolder.load(Textures::Flower, "images/flower.png");
    mTextureHolder.load(Textures::HealthHunger, "images/SleekBars.png");
    mTextureHolder.load(Textures::Walls, "images/walls.png");
}

void Game::generateFlower()
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



Game::~Game()
{
    delete mMap;
}
