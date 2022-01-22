#pragma once

#include "./Resources/ResourceHolder.h"
#include "./Resources/ResourceIdentifiers.h"
#include "./Machine/StateStack.h"
#include "PlayerInput.h"


#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>


class Application
{
public:
	Application();
	void run();


private:
	void loadFonts();
	void loadTextures();
	void loadSounds();
	void processInput();
	void update(double dt);
	void render();

	void registerStates();


private:
	const double TimePerFrame = 1.0f/60.0f;

	sf::RenderWindow mWindow;
	TextureHolder mTextures;
	FontHolder mFonts;
	SoundBufferHolder mSounds;
	InputManager mInput;
	PlayerInput mPlayerInput;
	StateStack mStateStack;

	sf::Clock m_clock;
};