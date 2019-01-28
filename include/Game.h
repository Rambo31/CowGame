#ifndef GAME_H
#define GAME_H



#include<SFML/Window/Keyboard.hpp>
#include<SFML/Window/Event.hpp>

#include<SFML/Graphics/RenderWindow.hpp>
#include<SFML/Graphics/Text.hpp>
#include<SFML/Graphics/Font.hpp>


#include"ResourceHolder.h"
#include"ResourceIdentifiers.h"
#include"Flower.h"
#include"Cow.h"

class Game : private sf::NonCopyable
{
	public:
								Game();
                                ~Game();
		void					run();


	private:
	    void                    generateFlower(); //world


        void                    loadTextures(); //world
        void                    buildScene();//world


		void					processEvents();
		void					update(sf::Time elapsedTime);
		void					render();


		void					updateStatistics(sf::Time elapsedTime);
		void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);


	private:
		static const float		PlayerSpeed;
		static const sf::Time	TimePerFrame;


        TextureHolder           mTextureHolder;

		sf::RenderWindow		mWindow;
		sf::Font				mFont;
		sf::Text				mStatisticsText;
		sf::Time				mStatisticsUpdateTime;
		std::size_t				mStatisticsNumFrames;

		Flower                  mFlower; //world
		sf::Time                mFlowerGenTime;

        sf::String*             mMap;//world
        sf::IntRect             mWorldBounds;

		Cow				        mCow; //world
		Cow                     mAICow;

};

#endif // GAME_H
