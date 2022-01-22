#include "models/Monster.h"
#include "models/Floor.h"

// comstructor
Monster::Monster(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	DynamicObject(pos, size, SPEED_MONSTER,txt)
{

}
/* handle Colision with floor:
	if the floor exists, put the monster back
	If not, and the existing monster puts the monster in floor
*/
//========================================================================
void Monster::handleColision(Floor& obj)
{
	if (obj.isExsist())
		this->goBack();

	else if (this->m_isExist)
	{
		obj.handleColision(*this);
		this->m_isExist = false;
		m_position_before_floor = this->m_last_postion;
	}

	else
	{
		this->m_rec->setPosition(obj.getSprite().getPosition());
	}	
	
}

/*
	if the monster is exist (not inside the floor) normal back .
	if not, return to the previous place before the fall
*/
//========================================================================
void Monster::goBack()
{
	if (this->m_isExist)
	{
		DynamicObject::goBack();
	}
	else
	{
		this->m_isExist = true;
		this->m_rec->setPosition(m_position_before_floor);
	}
}

//========================================================================
void Monster::handleColision(Player& obj)
{
	
}

//========================================================================
void Monster::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}

