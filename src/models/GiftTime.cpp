#include "..\..\include\models\GiftTime.h"

// static definition
bool GiftTime::m_is_active = false;

// constructor
//========================================================================
GiftTime::GiftTime(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	Gift(pos, size, txt)
{
}

//========================================================================
bool GiftTime::isActive()
{
	if (m_is_active)
	{
		m_is_active = false;
		return true;
	}
	return false;
}

//========================================================================
void GiftTime::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}


//========================================================================
void GiftTime::handleColision(Player& obj)
{
	this->m_isExist = false;
	this->m_is_active = true;
	
}

