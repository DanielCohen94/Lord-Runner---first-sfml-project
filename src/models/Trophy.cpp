#include "models\Trophy.h"

//constructor
Trophy::Trophy(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	StaticObject(pos, size, txt)
{
}

// It will not be possible to stand for a prize
//=============================================================
bool Trophy::collisionWithStand(DynamicObject& obj, sf::Vector2f size)
{
	return false;
}
