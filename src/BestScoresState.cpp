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

    sortResults();


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

	int mSize = (mData.size() > 8) ? 8 : mData.size();

	for (int i = 0; i < mSize; i++)
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
    int mSize = mData.size();

    std::pair<sf::String, sf::String> mPair;


    for(int j = 1; j < mSize; j++)
    {
        for(int i = 0; i < mSize - j; i++)
        {
            if(compareStrings(mData[i + 1].second, mData[i].second))
            {

                std::cout<<i<<std::endl;

                mPair = mData[i];
                mData[i] = mData[i + 1];
                mData[i + 1] = mPair;
            }
        }
    }
}


bool BestScoresState::compareStrings(sf::String first, sf::String second)
{
    if(first.getSize() > second.getSize())
    {
        return true;
    }
    else if(first.getSize() < second.getSize())
    {
        return false;
    }

    for(int i = 0; i < first.getSize(); i++)
    {
        if(first[i] > second[i])
        {
            return true;
        }
        else if(first[i] < second[i])
        {
            return false;
        }
    }

    return false;
}
