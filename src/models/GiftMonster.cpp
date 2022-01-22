#include "..\..\include\models\GiftMonster.h"

// definition static
bool GiftMonster::m_is_active = false;

// constructor
GiftMonster::GiftMonster(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	Gift(pos, size, txt)
{
}

//========================================================================
bool GiftMonster::isActive()
{
	if (m_is_active)
	{
		m_is_active = false;
		return true;
	}
	return false;
}

//========================================================================
void GiftMonster::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}

//========================================================================
void GiftMonster::handleColision(Player& obj)
{
	this->m_isExist = false;
	this->m_is_active = true;
}

