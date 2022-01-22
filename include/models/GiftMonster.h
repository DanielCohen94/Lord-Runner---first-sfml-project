#pragma once

#include "../models/Gift.h"
/* ================================================
class GiftMonster 

	Adds monster to level
*/
class GiftMonster : public Gift
{
public:

	// Constractor / Distactor
	GiftMonster(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	~GiftMonster() = default;
	// virtual functions
	void virtual handleColision(DynamicObject& obj) override;
	void virtual handleColision(Player& obj) override;
	// static function
	static bool isActive();

private:
	static bool m_is_active;

};//end gift Monster