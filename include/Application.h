#ifndef APPLICATION_H
#define APPLICATION_H


#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Font.hpp>
#include<SFML/Graphics/Text.hpp>

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "Cow.h"
#include "StateStack.h"



class Application
{
    public:
                        Application();
        void            run();

    protected:
        void            processInput();
        void            update(sf::Time dt);
        void            render();

        void            registerStates();
    private:
        void			updateStatistics(sf::Time elapsedTime);
    private:

        static const sf::Time	TimePerFrame;

		sf::RenderWindow		mWindow;
		TextureHolder			mTextures;
	  	FontHolder				mFonts;
		Cow					    mCow;

		StateStack				mStateStack;

        sf::Text				mStatisticsText;
		sf::Time				mStatisticsUpdateTime;
		std::size_t				mStatisticsNumFrames;

};

#endif // APPLICATION_H
