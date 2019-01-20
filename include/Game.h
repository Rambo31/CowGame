#ifndef GAME_H
#define GAME_H


#include<SFML/System/Time.hpp>

#include<SFML/Window/Keyboard.hpp>
#include<SFML/Window/Event.hpp>

#include<SFML/Graphics/RenderWindow.hpp>
#include<SFML/Graphics/Text.hpp>
#include<SFML/Graphics/Font.hpp>


#include<string>

#include"ResourceHolder.h"
#include"ResourceIdentifiers.h"
#include"Flower.h"

class Game : private sf::NonCopyable
{
	public:
								Game();
		void					run();


	private:
	    void           generateFlowerPos();
        void                    updateCowAnimation(sf::Time elapsedTime);

        void                    loadTextures();
        void                    buildScene();


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

		Flower                  mFlower;
        std::unique_ptr<std::string> mMap;

		float                   curFrame;
		sf::Sprite				mPlayer;
		bool					mIsMovingUp;
		bool					mIsMovingDown;
		bool					mIsMovingRight;
		bool					mIsMovingLeft;
};

#endif // GAME_H
