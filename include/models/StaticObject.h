#pragma once
#include "models/Object.h"
#include "models/Monster.h"

// forward declaration
class Player;

/* ================================================
Abstract class StaticObject
	Represents all the static objects in the game
*/
class StaticObject : public Object
{

public:
	// Constractor / Distactor
	StaticObject(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	~StaticObject() = default;
	// public functions

	// ============= pure virtual functions ===============
	bool virtual collisionWithStand(DynamicObject& obj, sf::Vector2f size) = 0;
	void virtual handleColision(DynamicObject& obj) = 0;
	
	// ============= virual functions =====================
	void virtual render(sf::RenderWindow* window)override;
	void virtual resetExist();
	bool virtual collisionWithDig(sf::Vector2f);
	void virtual digMe(sf::Time time) {};
	bool virtual digMeFree(sf::Time time, DynamicObject& obj);
	
	// ============= empty functions ======================
	void virtual handleColision(Floor& obj) {};
	void virtual handleColision(Coin& obj) {};
	void virtual handleColision(Ladder& obj) {};
	void virtual handleColision(Ropes& obj) {};
	void virtual handleColision(Monster& obj) {};

protected:

private:

}; // end StaticObject