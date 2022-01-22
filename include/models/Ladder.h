#pragma once

#include "StaticObject.h"

/* ================================================
class Ladder
	static object that dynamic object can climb on him
*/
class Ladder : public StaticObject
{

public:
	// Constractor / Distactor
	Ladder(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	~Ladder() = default;
	// virtual functions
	void virtual handleColision(DynamicObject& obj) override;
	bool virtual collisionWithStand(DynamicObject& obj, sf::Vector2f size) override;

private:

}; // end Ladder