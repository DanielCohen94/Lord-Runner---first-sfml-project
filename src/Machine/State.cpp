#include "./Machine/State.h"
#include "./Machine/StateStack.h"


State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, SoundBufferHolder& sounds, InputManager& input, PlayerInput& playerInput)
	: window(&window)
	, textures(&textures)
	, fonts(&fonts)
	, sounds(&sounds)
	, input(&input)
	, playerInput(&playerInput)
{
}

State::State(StateStack& stack, Context context)
	: mStack(&stack)
	, mContext(context)
{
	mousePicture.setTexture(context.textures->get(Textures::MouseC));
	mousePicture.setOrigin(sf::Vector2f(mousePicture.getTexture()->getSize() / 4u));
//	mousePicture.setColor(sf::Color(255, 255, 255, 255));


	mContext.window->setMouseCursorVisible(false);
}

State::~State()
{
}

void State::updateCursor()
{
	mousePicture.setPosition
	(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*getContext().window)));
}

void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}

State::Context State::getContext() const
{
	return mContext;
}
