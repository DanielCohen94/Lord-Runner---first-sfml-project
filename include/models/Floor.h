#pragma once

#include "StaticObject.h"

// forward declaration
class DynamicObject;

/* ================================================
class Floor 
	Barriers that exist in the game.
	You can dig in them.
*/
class Floor : public StaticObject
{

public:
	// Constractor / Distactor
	Floor(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	~Floor() = default;
	const bool isFull(); // there is monster in floor

	// virtual functions
	void virtual handleColision(DynamicObject& obj) override;
	void virtual handleColision(Monster& obj) override;
	void virtual digMe(sf::Time time) override;
	void virtual resetExist() override;

	bool virtual collisionWithStand(DynamicObject& obj, sf::Vector2f size) override;
	bool virtual digMeFree(sf::Time time, DynamicObject& obj) override;
	bool virtual collisionWithDig(sf::Vector2f) override;

private:
	sf::Time m_t_deleted;
	bool m_full;
}; // end floor