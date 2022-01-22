#pragma once

#include <fstream>
#include <experimental/vector>
#include <string>
#include <memory>

#include "models/StaticObject.h"
#include "models/Monster.h"
#include "models/MonsterRand.h"
#include "models/MonsterHorizontal.h"
#include "models/MonsterSmart.h"
#include "models/Player.h"
#include "models/DynamicObject.h"
#include "models/Floor.h"
#include "models/Ladder.h"
#include "models/Coin.h"
#include "models/Ropes.h"

#include "Resources/ResourceHolder.h"
#include "Resources/ResourceIdentifiers.h"

/* ================================================
class Board

	Holds all objects in the game except the player
*/
class Board
{

public:
	// Constractor / Distactor
	Board();
	~Board();
	// public functions
	void initSizeData(size_t, size_t);
	void createObject(sf::Vector2f pos, ObjectType::ID type, TextureHolder& textures, Player* const player,bool);
	void update(const float& dt, Player* player);
	void newLevel();
	void updateMonsterData();
	void startLevelAgain();
	void digIn(sf::Time time,sf::Vector2f pos);
	bool releaseDisappears(sf::Time time, DynamicObject& creature);
	const sf::Vector2f getPlaceToAddMon() const;
	const sf::Vector2f getSize() const;
	void renderMonster(sf::RenderWindow* window);
	void renderStaticObj(sf::RenderWindow* window);

private:

	std::vector<std::unique_ptr<Monster>> m_monsters;
	std::vector<std::unique_ptr<StaticObject>> m_static_obj;
	
	sf::Vector2f m_avgPix;
	sf::Vector2f m_location_add_monster;
	
	std::vector<std::vector<char>> m_grid;

	// private functions
	std::unique_ptr<StaticObject> createStaticObject
	(ObjectType::ID type, sf::Vector2f pos, sf::Vector2f size, TextureHolder& textures,bool);
	std::unique_ptr<Monster> createMonster
	(ObjectType::ID type, sf::Vector2f pos, sf::Vector2f size, TextureHolder& textures, Player* const player);

	void updateMonsters(const float& dt);
	void updateCreature(const float& dt, DynamicObject& creacure);
	void collisionsStatic(DynamicObject& rec);
	void collisionsDynamic(DynamicObject& rec);
	bool HaveSomthingToStand(DynamicObject& creacure);
	bool isInRange(DynamicObject& creacure);

}; // end board



