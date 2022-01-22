#include "models/StaticObject.h"

// constructor
StaticObject::StaticObject
(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	Object(pos, size, txt)
{
	
}

//=============================================================
void StaticObject::render(sf::RenderWindow* window)
{
	if(m_isExist)
		this->Object::render(window);
}

// for reset level
//=============================================================
void StaticObject::resetExist()
{
	this->m_isExist = true;
}

// digger, floor is override
//=============================================================
bool StaticObject::collisionWithDig(sf::Vector2f)
{
	return false;
}

//=============================================================
bool StaticObject::digMeFree(sf::Time time,DynamicObject& obj)
{
	return false;
}


