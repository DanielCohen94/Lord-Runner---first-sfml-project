#include "PauseState.h"
#include "./Resources/ResourceHolder.h"
#include "./Resources/ResourceIdentifiers.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "./models/Coin.h"

PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
	, mBackgroundSprite()
	, mPausedText()
	, mElapsedTime(0.0f)
{
	m_isBackMenuSelected = false;
	m_isBackMenuPressed = false;
	m_isResetGameSelected = false;
	m_isResetGamePressed = false;
	m_backToGameSelected = false;
	m_backToGamePressed = false;
	m_pressed = false;

	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mPausedText.setFont(font);
	mPausedText.setString("Game Paused");
	mPausedText.setCharacterSize(100);
	mPausedText.setFillColor(sf::Color(76, 0, 153));
	centerOrigin(mPausedText);
	mPausedText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
	mPausedText.setOutlineColor(sf::Color::White);
	mPausedText.setOutlineThickness(5.0f);

	buildButtons(windowSize);

	m_sound.setBuffer(context.sounds->get(SoundEffect::Button));
	m_soundState.setBuffer(context.sounds->get(SoundEffect::Menu));
	m_soundState.setLoop(true);
	m_soundState.play();
}

PauseState::~PauseState()
{
	m_soundState.stop();
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mPausedText);

	for (auto button : m_buttons)
		window.draw(button);

	window.draw(mousePicture);

}

bool PauseState::update(double dt)
{
	if (m_pressed)
	{
		updateColorButton();
		mElapsedTime += dt;
		// move to state after one second
		if (mElapsedTime > 1.0f)
		{
			m_pressed = false;
			m_sound.pause();
			if (m_backToGameSelected)
			{
				requestStackPop();
			}
			else if (m_isBackMenuSelected)
			{
				Coin::resetCollected();
				requestStateClear();
				requestStackPush(States::Menu);
			}
			else if (m_isResetGameSelected)
			{
				requestStateClear();
				requestStackPush(States::Game);
			}
		}
	}
	this->updateCursor();
	this->updateByMouse();

	return true;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	sf::RenderWindow& window = *getContext().window;
	InputManager* input = getContext().input;
	if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_soundState.stop();
		requestStackPop();
	}

	if (event.MouseButtonPressed)
	{
		if (m_backToGamePressed = input->isSpriteClicked(m_buttons[ButtonsPause::BackToGame],
										sf::Mouse::Left, window))
		{
			m_backToGameSelected = true;
			m_isBackMenuSelected = false;
			m_isResetGameSelected = false;
			m_pressed = true;
			m_sound.play();
		}

		if (m_isBackMenuPressed = input->isSpriteClicked(m_buttons[ButtonsPause::BackToMenu],
															sf::Mouse::Left, window))
		{
			m_backToGameSelected = false;
			m_isBackMenuSelected = true;
			m_isResetGameSelected = false;
			m_pressed = true;
			m_sound.play();
		}


		if (m_isResetGamePressed = input->isSpriteClicked(m_buttons[ButtonsPause::Restart],
															sf::Mouse::Left, window))
		{
			m_isBackMenuSelected = false;
			m_backToGameSelected = false;
			m_isResetGameSelected = true;
			m_pressed = true;
			m_sound.play();
		}
		return true;
	}
	return false;
}

// private functions
void PauseState::centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
		std::floor(bounds.top + bounds.height / 2.f));
}

void PauseState::buildButtons(const sf::Vector2f& windowSize)
{
	sf::Text text;
	text.setFont(getContext().fonts->get(Fonts::Main));
	text.setCharacterSize(55);
	text.setStyle(sf::Text::Bold);

	for (size_t i = 0; i < ButtonsPause::Max; i++)
	{
		m_buttons.push_back(text);
		m_buttons[i].setFillColor(sf::Color::White);
		m_buttons[i].setOrigin(m_buttons[i].getLocalBounds().width / 2,
			m_buttons[i].getLocalBounds().height / 2);
		m_buttons[i].setPosition(sf::Vector2f(windowSize.x / 2.5,
			(windowSize.y / 2) + (i * 100)));
		m_buttons[i].setOutlineColor(sf::Color(76, 0, 153));
		m_buttons[i].setOutlineThickness(5.f);
	}
	m_buttons[ButtonsPause::BackToGame].setString("Back to Game");
	m_buttons[ButtonsPause::BackToMenu].setString("Back to Game Menu");
	m_buttons[ButtonsPause::Restart].setString("Restart Game");
}

void PauseState::updateColorButton()
{
	if (m_backToGameSelected)
	{
		m_buttons[ButtonsPause::BackToGame].setFillColor(sf::Color::Black);
		m_buttons[ButtonsPause::BackToMenu].setFillColor(sf::Color::White);
		m_buttons[ButtonsPause::Restart].setFillColor(sf::Color::White);
	}
	else if (m_isBackMenuSelected)
	{
		m_buttons[ButtonsPause::BackToGame].setFillColor(sf::Color::White);
		m_buttons[ButtonsPause::BackToMenu].setFillColor(sf::Color::Black);
		m_buttons[ButtonsPause::Restart].setFillColor(sf::Color::White);
	}
	else if (m_isResetGameSelected)
	{
		m_buttons[ButtonsPause::BackToGame].setFillColor(sf::Color::White);
		m_buttons[ButtonsPause::BackToMenu].setFillColor(sf::Color::White);
		m_buttons[ButtonsPause::Restart].setFillColor(sf::Color::Black);
	}
}

void PauseState::updateByMouse()
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
