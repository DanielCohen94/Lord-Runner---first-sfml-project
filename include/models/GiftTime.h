#pragma once


#include "../models/Gift.h"
/* ================================================
class GiftTime

	Adds time to level
*/
class GiftTime : public Gift
{
public:
	// Constractor / Distactor
	GiftTime(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	~GiftTime() = default;
	// virtual functions
	void virtual handleColision(DynamicObject& obj) override;
	void virtual handleColision(Player& obj) override;
	// static function
	static bool isActive();

private:
	static bool m_is_active;

}; // GiftTime