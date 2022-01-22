#pragma once

#include "models/DynamicObject.h"

/* ================================================
Abstract class Monster

	Responsible for all the monsters in the game
*/
class Monster : public DynamicObject
{

public:

	// Constractor / Distactor
	Monster(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	virtual ~Monster() = default;
	
	// virtual functions
	void virtual goBack() override;
	void virtual handleColision(Floor& obj)override;
	void virtual handleColision(Player& obj) override;
	void virtual handleColision(DynamicObject& obj)override;
	// empty functions
	void virtual handleColision(Monster& obj) {};
	void virtual handleColision(Coin& obj) {};
	void virtual handleColision(GiftLife& obj) {};
	void virtual handleColision(GiftTime& obj) {};
	void virtual handleColision(GiftScore& obj) {};
	void virtual handleColision(GiftMonster& obj) {};
	void virtual handleColision(GiftStain& obj) {};

private:
	sf::Vector2f m_position_before_floor; // position before Fell to the floor

}; // end Monster