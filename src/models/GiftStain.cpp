#include "..\..\include\models\GiftStain.h"

// static definition
bool GiftStain::m_is_active = false;
sf::Clock GiftStain::m_clock;

// constructor
//========================================================================
GiftStain::GiftStain(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	Gift(pos, size, txt)
{
}

//========================================================================
bool GiftStain::isActive()
{
	if (m_is_active && m_clock.getElapsedTime().asSeconds() < 4)
	{
		return true;
	}
	else if(m_is_active && m_clock.getElapsedTime().asSeconds() > 4)
	{
		m_is_active = false;
		return false;
	}
	return false;
}

//========================================================================
void GiftStain::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}

//========================================================================
void GiftStain::handleColision(Player& obj)
{
	this->m_isExist = false;
	this->m_is_active = true;
	this->m_clock.restart();
}

