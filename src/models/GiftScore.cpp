#include "..\..\include\models\GiftScore.h"

// constructor
GiftScore::GiftScore(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	Gift(pos, size, txt)
{
}

//========================================================================
void GiftScore::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}

//========================================================================
void GiftScore::handleColision(Player& obj)
{
	this->m_isExist = false;
}
