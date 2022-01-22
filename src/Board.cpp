#include "Board.h"
#include <ctype.h>

// constructor
Board::Board()
{
}

// distructor
Board::~Board() 
{
}

// return unique ptr to monster  
//===================================================================
std::unique_ptr<Monster> Board::createMonster
(ObjectType::ID type, sf::Vector2f pos, sf::Vector2f size,
	TextureHolder& textures,Player * const player )
{
	if (type == ObjectType::MonsterChar)
	{
		int r = rand() % KindMonsters::Max;
		switch (r)
		{
		case KindMonsters::Rand:
			return std::make_unique<MonsterRand>(pos, size, &textures.get(Textures::MonsterRand));
		case KindMonsters::Horizontal:
			return std::make_unique<MonsterHorizontal>(pos, size, &textures.get(Textures::MonsterRL));
		case KindMonsters::Smart:
			return std::make_unique<MonsterSmart>
				(pos, size, &textures.get(Textures::MonsterSmart), player);
		}
	}
	return nullptr;
}

// return unique ptr to static object
//===================================================================
std::unique_ptr<StaticObject> Board::createStaticObject
(ObjectType::ID type, sf::Vector2f pos, sf::Vector2f size, TextureHolder& textures ,bool onTime)
{
	switch (type)
	{
	case ObjectType::FloorChar:
		return std::make_unique<Floor>(pos, size, &textures.get(Textures::Wall));
	case ObjectType::RopesChar:
		return std::make_unique<Ropes>(pos, size, &textures.get(Textures::Ropes));
	case ObjectType::LadderChar:
		return std::make_unique<Ladder>(pos, size, &textures.get(Textures::Ladder));
	case ObjectType::CoinChar:
		m_location_add_monster = pos;
		return std::make_unique<Coin>(pos, size, &textures.get(Textures::Coin));
	case ObjectType::GiftChar:
		int r;
		if(onTime)
			r = rand() % KindGifts::Max;
		else
			r = rand() % KindGifts::Max - 1;
		switch (r)
		{
		case KindGifts::Life:
			return std::make_unique<GiftLife>(pos, size, &textures.get(Textures::Gifts));
		case KindGifts::Score:
			return std::make_unique<GiftScore>(pos, size, &textures.get(Textures::Gifts));
		case KindGifts::Monster:
			return std::make_unique<GiftMonster>(pos, size, &textures.get(Textures::Gifts));
		case KindGifts::Stain:
			return std::make_unique<GiftStain>(pos, size, &textures.get(Textures::Gifts));
		case KindGifts::Time:
			return std::make_unique<GiftTime>(pos, size, &textures.get(Textures::Gifts));
		}
	}
	return nullptr;
}

// init size of board and size of grid-static
//===================================================================
void Board::initSizeData(size_t y, size_t x )
{
	m_avgPix.x = (COLL_GAME_SCREEN / (float)x);
	m_avgPix.y = (ROW_GAME_SCREEN / (float)y);

	m_grid.resize(y);

	for (int i = 0; i < y;i++)
		m_grid[i].resize(x);
}

/*
	create Object :
	Aided by auxiliary functions of monster building and static object building.
	Finally puts them into the appropriate vector
*/
//===================================================================
void Board::createObject
(sf::Vector2f pos, ObjectType::ID type,
	TextureHolder& textures, Player* player,bool onTime)
{
	std::unique_ptr<Monster> movable =
		createMonster(type,pos, m_avgPix, textures,player);
	if (movable)
	{
		m_monsters.push_back(std::move(movable));
		return;
	}

	std::unique_ptr<StaticObject> unmovable = 
		createStaticObject(type, pos, m_avgPix, textures,onTime);
	if (unmovable)
	{
		m_grid[(int)pos.y][(int)pos.x] = (char)type;
		m_static_obj.push_back(std::move(unmovable));
		return;
	}
}

// resatart to all objects
//===================================================================
void Board::startLevelAgain()
{
	for (int i = 0; i < m_monsters.size();i++)
	{
		m_monsters[i]->setFirstPos();
	}
	for (int i = 0;i < m_static_obj.size();i++)
	{
		m_static_obj[i]->resetExist();
	}
}

//===================================================================
void Board::digIn(sf::Time time, sf::Vector2f pos)
{
	for (int i = 0;i < m_static_obj.size();i++)
	{
		if (m_static_obj[i]->collisionWithDig(pos))
		{
			m_static_obj[i]->digMe(time);
		}
	}
}

//===================================================================
bool Board::releaseDisappears(sf::Time time,DynamicObject& creature)
{	
	bool dead = false;
	for (int i = 0;i < m_static_obj.size();i++)
	{
		if (m_static_obj[i]->digMeFree(time, creature))
			dead = true;
	}
	return dead;
}

// game state sends the player and asks the board to update the data
//===================================================================
void Board::update(const float& dt,Player* player)
{
	this->updateCreature(dt, *player);
	this->updateMonsters(dt);
	this->collisionsDynamic(*player);
}

// clear vectors
//===================================================================
void Board::newLevel()
{
	this->m_monsters.clear();
	this->m_static_obj.clear();
}

// give to smart monster the grid-static
//===================================================================
void Board::updateMonsterData()
{
	for (int i = 0; i < m_monsters.size();i++)
	{
		m_monsters[i]->setGrid(m_grid);
	}
}

//===================================================================
const sf::Vector2f Board::getSize() const
{
	return this->m_avgPix;
}

// get Dynamic Object and chack collision with the static vector
//===================================================================
void Board::collisionsStatic(DynamicObject& creature)
{
	for (int i = 0; i < m_static_obj.size();i++)
	{
		if (m_static_obj[i]->collisionWith(creature))
			m_static_obj[i]->handleColision(creature);
	}
}

// get Dynamic Object and chack collision with the monster vector
//===================================================================
void Board::collisionsDynamic(DynamicObject& creature)
{
	for (int i = 0; i < m_monsters.size();i++)
	{
		if (m_monsters[i]->collisionWith(creature))
			m_monsters[i]->handleColision(creature);
	}
}

//===================================================================
const sf::Vector2f Board::getPlaceToAddMon() const
{
	return m_location_add_monster;
}

//===================================================================
bool Board::HaveSomthingToStand(DynamicObject& creacure)
{
	for (int i = 0; i < m_static_obj.size();i++)
	{
		if (m_static_obj[i]->collisionWithStand(creacure,m_avgPix))
			return true;
	}
		
	return false;
}

// if Dynamic Object is in range of the window
//===================================================================
bool Board::isInRange(DynamicObject& dynObj)
{
	if (m_avgPix.x / 2u - 4.5 < dynObj.getSprite().getPosition().x
		&& m_avgPix.y / 2u - 4.5 < dynObj.getSprite().getPosition().y
		&& COLL_GAME_SCREEN - (m_avgPix.y / 2u) > dynObj.getSprite().getPosition().x
		&& ROW_GAME_SCREEN - (m_avgPix.y / 8u) > dynObj.getSprite().getPosition().y)
		return true;
	return false;
}

/*
	update Creature :
	Gets a dynamic object
	Asks him to move and checks his collisions with static objects
*/
//===================================================================
void Board::updateCreature(const float& dt, DynamicObject& creacure)
{
	creacure.resetData();
	creacure.updateDirection(dt);

	if(!HaveSomthingToStand(creacure))
		creacure.setDirectionDown();

	creacure.move(dt);

	if (!isInRange(creacure))
		creacure.goBack();

	collisionsStatic(creacure);
}

// send all monster to update creature
//===================================================================
void Board::updateMonsters(const float& dt)
{
	for (int i = 0; i < m_monsters.size();i++)
	{
		this->updateCreature(dt, *m_monsters[i]);
	}
}

//===================================================================
void Board::renderMonster(sf::RenderWindow* target)
{
	for (int i = 0; i < m_monsters.size();i++)
		m_monsters[i]->render(target);
}

//===================================================================
void Board::renderStaticObj(sf::RenderWindow* window)
{
	for (int i = 0; i < m_static_obj.size();i++)
		m_static_obj[i]->render(window);
}