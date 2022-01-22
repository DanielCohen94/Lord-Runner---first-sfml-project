#pragma once

#include "StaticObject.h"
/* ================================================
class Ropes
	static object that dynamic object can move right and left
	on it without having a floor underneath
*/
class Ropes : public StaticObject
{
public:
	// Constractor / Distactor
	Ropes(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	~Ropes() = default;
	// virtual functions
	void virtual handleColision(DynamicObject& obj) override;
	bool virtual collisionWithStand(DynamicObject& obj, sf::Vector2f size) override;

private:

};// end Ropes