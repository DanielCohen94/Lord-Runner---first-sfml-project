#pragma once

#include "StaticObject.h"
#include "DynamicObject.h"

/* ================================================
Abstract class Trophy
	Represents all the static objects that
	the player takes from the board during the game
*/
class Trophy : public StaticObject
{

public:
	// Constractor / Distactor
	Trophy(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	virtual ~Trophy() = default;
	// virtual functions
	bool collisionWithStand(DynamicObject& obj, const sf::Vector2f) override;
	void virtual handleColision(DynamicObject& obj) {};
	void virtual handleColision(Player& obj) = 0;

private:

}; // end Trophy
