#include<cstdlib>
#include<ctime>

#include "Game.h"
#include "StringHelpers.h"


const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game()
: mWindow(sf::VideoMode(640, 480), "SFML Application", sf::Style::Close)
, mCow()
, mFlower()
, mFont()
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
, mIsMovingUp(false)
, mIsMovingDown(false)
, mIsMovingRight(false)
, mIsMovingLeft(false)
, mIsGoingToEat(false)
, curFrame(0)
, mMap(new sf::String[mWindow.getSize().y / 32])
{

    for(int i = 0; i < mWindow.getSize().y / 32; i++)
    {
        for(std::size_t j = 0; j < mWindow.getSize().x / 32; j++)
        {
            mMap[i].insert(j, "0");
        }
    }

    loadTextures();
    buildScene();


	mFont.loadFromFile("fonts/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(13);
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
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;

	updateCowAnimation(elapsedTime);

	updateCowCollisionWithEatable();

	mCow.mSprite.move(movement * elapsedTime.asSeconds());

	updateCowCollisionWithBarriers(true);
	updateCowCollisionWithBarriers(false);

}

void Game::render()
{
    sf::Color color(52, 171, 24);

	mWindow.clear(color);

    for(int i = 0; i < mWindow.getSize().y / 32; i++)
    {
        for(int j = 0; j < mWindow.getSize().x / 32; j++)
        {
            if(*(mMap[i].begin() + j) == '1')
            {
                mFlower.mSprite.setPosition(j * 32, i * 32);
                mWindow.draw(mFlower.mSprite);
            }
        }
    }



	mWindow.draw(mCow.mSprite);
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
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
    else if (key == sf::Keyboard::Space)
        mIsGoingToEat = isPressed;
}

void Game::updateCowAnimation(sf::Time elapsedTime)
{
    curFrame = curFrame + elapsedTime.asMilliseconds() * 0.01f;

    if((int)curFrame > 3)
    {
        curFrame-= 3;
    }

    if(mIsMovingUp)
    {
        mCow.mSprite.setTextureRect(sf::IntRect((int)curFrame * 128, 0, 128, 128));
    }
    else if(mIsMovingLeft)
    {
        mCow.mSprite.setTextureRect(sf::IntRect((int)curFrame * 128, 128, 128, 128));
    }
    else if(mIsMovingDown)
    {
        mCow.mSprite.setTextureRect(sf::IntRect((int)curFrame * 128, 256, 128, 128));
    }
    else if(mIsMovingRight)
    {
        mCow.mSprite.setTextureRect(sf::IntRect((int)curFrame * 128, 384, 128, 128));
    }

}


void Game::buildScene()
{

    sf::Texture& cow_texture = mTextureHolder.get(Textures::Cow);

    mCow.mSprite.setTexture(cow_texture);
	mCow.mSprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
	mCow.mSprite.setPosition(100.f, 100.f);



	sf::Texture& flower_tex = mTextureHolder.get(Textures::Flower);
    mFlower.mSprite.setTexture(flower_tex);
    mFlower.mSprite.setTextureRect(sf::IntRect(64, 64, 32, 32));

    for(int i = 0; i < 3; i++)
        generateFlowerPos();

}

void Game::loadTextures()
{
    mTextureHolder.load(Textures::Cow, "images/cow.png");
    mTextureHolder.load(Textures::Flower, "images/flower.png");
}

void Game::generateFlowerPos()
{
    static unsigned int seed = 0;

    srand(time(0) + seed++);


    int x_pos = rand() % (mWindow.getSize().x / 32);
    int y_pos = rand() % (mWindow.getSize().y / 32);


    if(*(mMap[y_pos].begin() + x_pos) != '1')
    {
        mMap[y_pos].erase(x_pos);
        mMap[y_pos].insert(x_pos, "1");
    }
}

void Game::updateCowCollisionWithEatable()
{
    if(mIsGoingToEat)
    {
        for(int i = mCow.mSprite.getGlobalBounds().left / 32;
        i < (mCow.mSprite.getGlobalBounds().left + mCow.mSprite.getGlobalBounds().width) / 32;
        i++)
        {
            for(int j = mCow.mSprite.getGlobalBounds().top / 32;
            j < (mCow.mSprite.getGlobalBounds().top + mCow.mSprite.getGlobalBounds().height) / 32;
            j++)
            {
                if(*(mMap[j].begin() + i) == '1')
                {
                    mMap[j].erase(i);
                    mMap[j].insert(i, '0');
                }
            }
        }
    }
}

void Game::updateCowCollisionWithBarriers(bool isXDir)
{
    if(isXDir)
    {
        if(mCow.mSprite.getGlobalBounds().left < 0)
        {
            mCow.mSprite.setPosition(0, mCow.mSprite.getPosition().y);
        }
        else if(mCow.mSprite.getGlobalBounds().left +
                mCow.mSprite.getGlobalBounds().width >
                mWindow.getSize().x)
        {

            mCow.mSprite.setPosition(mWindow.getSize().x -
                mCow.mSprite.getGlobalBounds().width,
                mCow.mSprite.getPosition().y);

        }
    }
    else
    {
        if(mCow.mSprite.getGlobalBounds().top < 0)
        {
            mCow.mSprite.setPosition(mCow.mSprite.getPosition().x, 0);
        }
        else if(mCow.mSprite.getGlobalBounds().top +
                mCow.mSprite.getGlobalBounds().height >
                mWindow.getSize().y)
        {
            mCow.mSprite.setPosition(mCow.mSprite.getPosition().x,
                mWindow.getSize().y -
                mCow.mSprite.getGlobalBounds().height);
        }
    }
}

Game::~Game()
{
    delete mMap;
}
