#include "FinalState.h"
#include "./Resources/ResourceHolder.h"
#include "./Resources/ResourceIdentifiers.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


FinalState::FinalState(StateStack& stack, Context context)
	: State(stack, context), mElapsedTime(0.0f), m_backToMenu(false), m_limit(15)
{
	sf::Vector2u textureSize, windowSize;

	windowSize = context.window->getSize();
	textureSize = context.textures->get(Textures::Menu).getSize();

	// get texture state
	sf::Texture& texture = context.textures->get(Textures::Menu);
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setScale((float)windowSize.x / textureSize.x,
		(float)windowSize.y / textureSize.y);

	// get font state
	sf::Font& font = context.fonts->get(Fonts::Main);
	m_title.setFont(font);
	// display if user win
	if (context.playerInput->getSuccess())
	{
		m_title.setString("Congratulations! You Win!!\n\tYour score is: "
						+ std::to_string(context.playerInput->getScore()));
		m_soundState.setBuffer(context.sounds->get(SoundEffect::Win));
	}
	else
	{
		// user lose
		m_title.setString("Sorry, You Lose!\n\tYour score is: "
						+ std::to_string(context.playerInput->getScore()));
		m_soundState.setBuffer(context.sounds->get(SoundEffect::Lose));
	}
	m_soundState.setLoop(true);
	m_title.setFillColor(sf::Color::Cyan);
	m_title.setCharacterSize(100);
	centerOrigin(m_title);
	m_title.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

	// second text
	m_message.setFont(font);
	m_message.setString("Please enter your name");
	m_message.setFillColor(sf::Color::White);
	m_message.setCharacterSize(50);
	m_message.setOrigin(m_message.getLocalBounds().width / 2,
		m_message.getLocalBounds().height / 2);
	m_message.setPosition(sf::Vector2f(windowSize.x / (unsigned)2.5,
		(windowSize.y / 2u) + (unsigned)100));

	// text input from user
	playerText.setFont(font);
	playerText.setCharacterSize(50);
	playerText.setFillColor(sf::Color::Red);
	centerOrigin(playerText);
	playerText.setPosition(sf::Vector2f(windowSize.x / 2.5, (windowSize.y / 2) + 200));

	// get score user
	m_score_player = new std::string(std::to_string(context.playerInput->getScore()));
	m_score = context.playerInput->getScore();

	m_soundState.play();
}

FinalState::~FinalState()
{
	delete m_score_player;
	delete m_name;
}

void FinalState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(m_title);
	window.draw(m_message);
	window.draw(playerText);

}

bool FinalState::update(double dt)
{
	if (m_backToMenu)
	{
		// save values and return to menu state
		getContext().playerInput->updateScore(*m_name, m_score);
		requestStateClear();
		requestStackPush(States::Menu);
	}

	return true;
}

bool FinalState::handleEvent(const sf::Event& event)
{
	if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_soundState.pause();
		requestStateClear();
	}
	else if (event.type == sf::Event::TextEntered)
	{
		// if get text from keyboard
		if (event.text.unicode < SpecialKeyboard::MAX)
		{
			if (!inputLogic(event.text.unicode))
			{
				m_backToMenu = true;
			}
		}
	}
	return true;
}

// private functions
void FinalState::centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
		std::floor(bounds.top + bounds.height / 2.f));
}

bool FinalState::inputLogic(int charTyped)
{
	if (charTyped != SpecialKeyboard::DELETE_KEY &&
		charTyped != SpecialKeyboard::ENTER_KEY &&
		charTyped != SpecialKeyboard::ESCAPE_KEY)
	{
		playerInput += static_cast<char>(charTyped);

		if (playerInput.getSize() == m_limit)
			return false;
		playerText.setString(playerInput);
	}
	else if (charTyped == SpecialKeyboard::DELETE_KEY)
	{
		if (playerInput.getSize() > 0)
			deleteLastChar();
		playerText.setString(playerInput + "_");
	}
	else if (charTyped == SpecialKeyboard::ENTER_KEY)
	{
		if (playerInput.getSize() > 0)
			m_name = new std::string(playerInput.toAnsiString());
		else
			m_name = new std::string("");
		return false;
	}
	return true;
}

void FinalState::deleteLastChar()
{
	sf::String tempString = "";

	for (int i = 0; i < playerInput.getSize() - 1; i++)
		tempString += playerInput[i];

	playerInput = tempString;
	playerText.setString(playerInput);
	
}
