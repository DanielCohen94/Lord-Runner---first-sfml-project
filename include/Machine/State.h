#pragma once

#include "StateIdentifiers.h"
#include "../Resources/ResourceHolder.h"
#include "../Resources/ResourceIdentifiers.h"
#include "../InputManager.h"
#include "../PlayerInput.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>


namespace sf
{
	class RenderWindow;
}

class StateStack;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts,
			    SoundBufferHolder& sounds, InputManager& input, PlayerInput& playerInput);

		sf::RenderWindow* window;
		TextureHolder* textures;
		FontHolder* fonts;
		SoundBufferHolder* sounds;
		InputManager* input;
		PlayerInput* playerInput;
	};


public:
	State(StateStack& stack, Context context);
	virtual				~State();

	virtual void draw() = 0;
	virtual bool update(double dt) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;

	void updateCursor();

	virtual void pause(){}
	virtual void start(){}


protected:
	void requestStackPush(States::ID stateID);
	void requestStackPop();
	void requestStateClear();

	Context getContext() const;

	sf::Sprite mousePicture;

private:
	StateStack* mStack;
	Context mContext;
};