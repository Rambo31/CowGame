#include "Application.h"
#include"GameState.h"
#include"TitleState.h"
#include"MenuState.h"
#include"BestScoresState.h"
#include"GameOverState.h"
#include"DataInputState.h"
#include "StringHelpers.h"

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
: mWindow(sf::VideoMode(1024, 600), "SFML Application", sf::Style::Fullscreen)
, mTextures()
, mFonts()
, mCow(Cow::CowType::Player)
, mStateStack(State::Context(mWindow, mTextures, mFonts, mCow))
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
{

    mFonts.load(Fonts::Sansation, "fonts/Sansation.ttf");
    sf::Font& sansat_font = mFonts.get(Fonts::Sansation);

    mStatisticsText.setFont(sansat_font);
	mStatisticsText.setPosition(0.f, 0.f);
	mStatisticsText.setCharacterSize(13);

 	registerStates();
	mStateStack.pushState(States::Title);

}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			if (mStateStack.isEmpty())
				mWindow.close();
		}
        updateStatistics(dt);
		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::render()
{
    mWindow.clear(sf::Color::Black);

	mStateStack.draw();

	mWindow.draw(mStatisticsText);

	mWindow.display();
}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<DataInputState>(States::DataInput);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<BestScoresState>(States::Scores);
	mStateStack.registerState<GameState>(States::Game);
	//mStateStack.registerState<PauseState>(States::Pause);
	mStateStack.registerState<GameOverState>(States::GameOver);

}


void Application::updateStatistics(sf::Time elapsedTime)
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
