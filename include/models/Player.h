#pragma once

#include <SFML/Audio.hpp>

#include "models/DynamicObject.h"
#include "../macros.h"
#include "../Resources/ResourceIdentifiers.h"
#include "Coin.h"
#include "GiftLife.h"
#include "GiftTime.h"
#include "GiftScore.h"
#include "GiftMonster.h"
#include "GiftStain.h"

// forward declaration
class Monster;

/* ================================================
class Player
	initialized once per game.
	At each level gets positioned and resized
*/

class Player : public DynamicObject
{
	
public:
	// Constractor / Distactor
	Player(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt, SoundBufferHolder& sounds);
	~Player() = default;
	// new level - new data
	void newData(sf::Vector2f pos, sf::Vector2f size);

	// virtual functions
	void virtual resetData()override;
	void virtual updateDirection(const float& dt) override;
	void virtual handleColision(Floor& obj) override;
	void virtual handleColision(Coin& obj) override;
	void virtual handleColision(Monster& obj) override;
	void virtual handleColision(GiftLife& obj) override;
	void virtual handleColision(GiftTime& obj) override;
	void virtual handleColision(GiftScore& obj) override;
	void virtual handleColision(GiftMonster& obj) override;
	void virtual handleColision(GiftStain& obj) override;
	// empty function 
	void virtual handleColision(DynamicObject& obj) {};
	void virtual handleColision(Player& obj) {};
	// dig functions
	bool dig();
	sf::Vector2f getMovementDig(sf::Vector2f size) const;
	// access functions
	const bool isInjured();
	const int getLife() const;
	const int getScore() const;
	const int getLevel() const;

	void injured();
	void newLevel();

private:
	int m_life;
	int m_score;
	bool m_is_injured;
	int m_numLevel;
	int m_direction_dig;
	
	sf::Sound m_soundGetCoin;
	sf::Sound m_soundInjured;
	sf::Sound m_soundLifeUp;
	sf::Sound m_soundScoreUp;
	sf::Sound m_soundStain;
	sf::Sound m_soundAddMon;
	sf::Sound m_soundAddTime;

}; // end Player