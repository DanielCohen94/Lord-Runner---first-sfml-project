#include "ErrorState.h"
#include "./Resources/ResourceHolder.h"
#include "./Resources/ResourceIdentifiers.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


ErrorState::ErrorState(StateStack& stack, Context context)
	: State(stack, context), mElapsedTime(0.0f)
{
	sf::Vector2u textureSize, windowSize;

	windowSize = context.window->getSize();
	textureSize = context.textures->get(Textures::Menu).getSize();

	// get texture state
	sf::Texture& texture = context.textures->get(Textures::Menu);
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setScale((float)windowSize.x / textureSize.x,
		(float)windowSize.y / textureSize.y);

	// get sound state
	m_soundState.setBuffer(context.sounds->get(SoundEffect::Menu));
	m_soundState.setLoop(true);

	// get font state
	sf::Font& font = context.fonts->get(Fonts::Main);
	// title state
	m_title.setFont(font);
	m_title.setString("Sorry, but an error ocurred");
	m_title.setFillColor(sf::Color(76, 0, 153));
	m_title.setCharacterSize(100);
	centerOrigin(m_title);
	m_title.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

	m_soundState.play();
}

void ErrorState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	// Create dark, semitransparent background
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(m_title);
}

bool ErrorState::update(double dt)
{
	// Show state for 3 seconds, after return to menu
	mElapsedTime += (float)dt;
	if (mElapsedTime > 3.0f)
	{
		requestStateClear();
		requestStackPush(States::Menu);
	}
	return false;
}

bool ErrorState::handleEvent(const sf::Event&)
{
	return false;
}

void ErrorState::centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
		std::floor(bounds.top + bounds.height / 2.f));
}
