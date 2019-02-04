#include <SFML/Graphics/RenderWindow.hpp>


#include "BestScoresState.h"
#include "Utility.h"
#include "ResourceHolder.h"
#include<iostream>

BestScoresState::BestScoresState(StateStack& stack, Context context)
: State(stack, context)
, mNames()
, mScores()
, mData()
, mResults()
{
    readEntryFromFile(mData, "resources/Scores.txt");

    //sortResults();


    mResults.setFont(context.fonts->get(Fonts::Sansation));

    mNames.setFont(context.fonts->get(Fonts::Sansation));
	mNames.setString("NAME");
	centerOrigin(mNames);
	mNames.setPosition(context.window->getView().getSize().x / 2.f - 256.f, 64.f);

    mScores.setFont(context.fonts->get(Fonts::Sansation));
	mScores.setString("SCORE");
	centerOrigin(mScores);
	mScores.setPosition(context.window->getView().getSize().x / 2.f + 256.f, 64.f);
}

void BestScoresState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mNames);
	window.draw(mScores);

	for (int i = 0; i < mData.size(); i++)
    {
        mResults.setString(mData[i].first);
        centerOrigin(mResults);
        mResults.setPosition(mNames.getPosition() + sf::Vector2f(0, 64.f * (i + 1)));
        window.draw(mResults);

        mResults.setString(mData[i].second);
        centerOrigin(mResults);
        mResults.setPosition(mScores.getPosition() + sf::Vector2f(0, 64.f * (i + 1)));
        window.draw(mResults);

    }
}

bool BestScoresState::update(sf::Time dt)
{

	return true;
}

bool BestScoresState::handleEvent(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if (event.type == sf::Event::KeyPressed)
	{
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return true;
}


void BestScoresState::sortResults()
{
    int mSize;

    std::pair<sf::String, sf::String> mPair;

    if(mData.size() > 8)
    {
        mSize = 8;
    }
    else
    {
        mSize = mData.size();
    }


    for(int i = 0; i < mSize - 1; i++)
    {
        if(mData[i + 1].second > mData[i].second)
        {
            mPair = mData[i];
            mData[i] = mData[i + 1];
            mData[i + 1] = mPair;
        }
    }
}
