#include "MenuState.h"
#include "./Resources/ResourceHolder.h"
#include "./Resources/ResourceIdentifiers.h"
#include "InputManager.h"
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context), mEffectTime(0.0f)
{
	// booleans for buttons
	m_isPlayButtonSelected = false;
	m_isPlayButtonPressed = false;
	m_isSettingsButtonSelected = false;
	m_isSettingsButtonPressed = false;
	m_isRecordsPressed = false;
	m_isRecordsSelected = false;

	sf::Vector2u textureSize, windowSize;

	windowSize = context.window->getSize();
	textureSize = context.textures->get(Textures::Menu).getSize();

	// get texture background
	sf::Texture& texture = context.textures->get(Textures::Menu);
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setScale((float)windowSize.x / textureSize.x,
								(float)windowSize.y / textureSize.y);

	// get font
	sf::Font& font = context.fonts->get(Fonts::Main);
	// title state
	m_title.setFont(font);
	m_title.setString("Lord Runner Game");
	m_title.setFillColor(sf::Color(76,0,153));
	m_title.setOutlineColor(sf::Color::White);
	m_title.setOutlineThickness(5.f);
	m_title.setCharacterSize(100);
	centerOrigin(m_title);
	m_title.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
	// buttons state
	buildButtons(windowSize);

	// sounds state
	m_sound.setBuffer(context.sounds->get(SoundEffect::Button));
	m_sound.setPlayingOffset(sf::seconds(2.f));
	m_soundState.setBuffer(context.sounds->get(SoundEffect::Menu));
	m_soundState.setLoop(true);
	// music by settings
	aload_music = context.playerInput->getUserSound();

	if (aload_music)
		m_soundState.play();
	else
	{
		m_soundState.stop();
		m_sound.stop();
	}
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);

	window.draw(m_title);

	for (auto button : m_buttons)
		window.draw(button);
	
	window.draw(mousePicture);

}

bool MenuState::update(double dt)
{
	if (m_pressed)
	{
		mEffectTime += (float)dt;
		updateColorButton();
		// move to new state after second
		if (mEffectTime >= 1.0f)
		{
			m_pressed = false;
			mEffectTime = 0.0f;
			m_sound.stop();
			if (m_isPlayButtonSelected)
			{
				requestStackPop();
				requestStackPush(States::Game);
			}
			else if (m_isSettingsButtonSelected)
			{
				requestStackPop();
				requestStackPush(States::Settings);
			}
			else if (m_isRecordsSelected)
			{
				requestStackPop();
				requestStackPush(States::Records);
			}
		}
	}

	this->updateCursor();

	this->updateByMouse();

	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	sf::RenderWindow& window = *getContext().window;
	InputManager* input = getContext().input;
	if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_soundState.stop();
		requestStateClear();
	}

	if (event.MouseButtonPressed)
	{
		if (m_isPlayButtonPressed = input->isSpriteClicked(m_buttons[ButtonsMenu::PlayGame],
																sf::Mouse::Left, window))
		{
			m_isPlayButtonSelected = true;
			m_isSettingsButtonSelected = false;
			m_isRecordsSelected = false;
			m_pressed = true;
			if(aload_music)
				m_sound.play();
		}

		if (m_isSettingsButtonPressed = input->isSpriteClicked(m_buttons[ButtonsMenu::GameSettings],
																	sf::Mouse::Left, window))
		{
			m_isSettingsButtonSelected = true;
			m_isPlayButtonSelected = false;
			m_isRecordsSelected = false;
			m_pressed = true;
			if (aload_music)
				m_sound.play();
		}

		if (m_isRecordsPressed = input->isSpriteClicked(m_buttons[ButtonsMenu::TopScores],
									sf::Mouse::Left, window))
		{
			m_isPlayButtonSelected = false;
			m_isSettingsButtonSelected = false;
			m_isRecordsSelected = true;
			m_pressed = true;
			if (aload_music)
				m_sound.play();
		}
		return true;
	}
	return false;
}
// private functions
void MenuState::buildButtons(const sf::Vector2u& windowSize)
{
	sf::Text text;
	text.setFont(getContext().fonts->get(Fonts::Main));
	text.setCharacterSize(55);
	text.setStyle(sf::Text::Bold);

	for (size_t i = 0; i < ButtonsMenu::Max; i++)
	{
		m_buttons.push_back(text);
		m_buttons[i].setFillColor(sf::Color::White);

		m_buttons[i].setOrigin(m_buttons[i].getLocalBounds().width / 2,
			m_buttons[i].getLocalBounds().height / 2);
		m_buttons[i].setPosition(sf::Vector2f(windowSize.x / 2.5,
			(windowSize.y / 2u) + (i * 100)));
		m_buttons[i].setOutlineColor(sf::Color(76, 0, 153));
		m_buttons[i].setOutlineThickness(5.f);

	}
	m_buttons[ButtonsMenu::PlayGame].setString("Play Game");
	m_buttons[ButtonsMenu::GameSettings].setString("Game Settings");
	m_buttons[ButtonsMenu::TopScores].setString("Top Scores");
}

void MenuState::centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
		std::floor(bounds.top + bounds.height / 2.f));
}

void MenuState::updateColorButton()
{
	if (m_isPlayButtonSelected)
	{
		m_buttons[ButtonsMenu::PlayGame].setFillColor(sf::Color::Black);
		m_buttons[ButtonsMenu::GameSettings].setFillColor(sf::Color::White);
		m_buttons[ButtonsMenu::TopScores].setFillColor(sf::Color::White);
	}
	else if (m_isSettingsButtonSelected)
	{
		m_buttons[ButtonsMenu::PlayGame].setFillColor(sf::Color::White);
		m_buttons[ButtonsMenu::GameSettings].setFillColor(sf::Color::Black);
		m_buttons[ButtonsMenu::TopScores].setFillColor(sf::Color::White);
	}
	else if (m_isRecordsSelected)
	{
		m_buttons[ButtonsMenu::PlayGame].setFillColor(sf::Color::White);
		m_buttons[ButtonsMenu::GameSettings].setFillColor(sf::Color::White);
		m_buttons[ButtonsMenu::TopScores].setFillColor(sf::Color::Black);
	}
}

void MenuState::updateByMouse()
{
	auto mouse_pos = getContext().input->GetMousePosition(*getContext().window);
	auto translated_pos = getContext().window->mapPixelToCoords(mouse_pos);

	for (auto& button : m_buttons)
	{
		// Rectangle-contains-point check
		if (button.getGlobalBounds().contains(translated_pos))
		{
			// Mouse is inside the sprite.
			button.setFillColor(sf::Color::Yellow);
		}
		else
			button.setFillColor(sf::Color::White);
	}
}
