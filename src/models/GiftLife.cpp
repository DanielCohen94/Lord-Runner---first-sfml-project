#include "..\..\include\models\GiftLife.h"

// constructor
//========================================================================
GiftLife::GiftLife(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	Gift(pos, size, txt)
{
}

//========================================================================
void GiftLife::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}

//========================================================================
void GiftLife::handleColision(Player& obj)
{
	this->m_isExist = false;
}