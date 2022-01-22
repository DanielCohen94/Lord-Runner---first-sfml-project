#include "models/MonsterSmart.h"
#include <queue> 
#include <cmath>
#include <stdlib.h> 
#include "models/Floor.h"

//constructor
//========================================================================
MonsterSmart::MonsterSmart
(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt,  Player* const p) :
	Monster(pos, size, txt), m_size(size),m_last_cell(0, 0), m_last_dir(0)
{
	m_copy_player = p;
}

/*
	get from bord mat-type char of static object 
*/
//========================================================================
void MonsterSmart::setGrid(std::vector<std::vector<char>>& grid)
{
	m_map = grid;
	this->buildVisited(2);
}

//========================================================================
bool MonsterSmart::isInRange(int row, int col)
{
	return (row >= 0 && col >= 0 && row < m_visited.size() && col < m_visited[0].size());
}

/*
1. Builds two points with matching indexes in the matrix according to
   the position of the player and the monster.

2. Rebuilds the matrix of the numbers each time according to
   the position of all the static objects.

3. After it is built it happens to the algorithm
  (in which the matrix of the numbers is destroyed and 
    therefore it is necessary to rebuild it every time)
*/
//========================================================================
void MonsterSmart::updateDirection(const float& dt)
{
	sf::Vector2i  monsterPosMap, playerPosMap;

	playerPosMap = this->getPosOnMat(m_copy_player);
	monsterPosMap = this->getPosOnMat(this);
	
	this->buildVisited(2);
	if (m_visited[playerPosMap.x][playerPosMap.y] != 2)
			this->buildVisited(1);
	
	m_dircetion = this->getDirectionSmartBfs(playerPosMap, monsterPosMap);

	this->SaveLastPosition();
}

//========================================================================
size_t MonsterSmart::getDirectionSmartBfs(sf::Vector2i playerPosMap, sf::Vector2i monsterPosMap)
{
	if (m_map.size() == 0 || m_visited.size() == 0)
		return -1;

	size_t i = 1;

	std::queue <NudeBfs> queueManager;
	std::vector<int> vec;
	vec.clear();
	// make nude source from monster index 
	NudeBfs source(monsterPosMap.x, monsterPosMap.y, vec);

	queueManager.push(source);
	bool moveTwo = false;

	while (!queueManager.empty()) {
		NudeBfs p = queueManager.front();
		queueManager.pop();

		if (!(p.row >= 0 && p.col >= 0 &&
			p.row < m_visited.size() && p.col < m_visited[0].size()))
			return -1;

		// to make the algoritm check only down direction 
		// if he in cell that hold 2
		if (m_map[p.row][p.col] == 2)
			moveTwo = true;
		else
			moveTwo = false;

		// Player found; 
		if (p.row == playerPosMap.x && p.col == playerPosMap.y)
		{
			// return the first direction
			if (!p.VecMov.empty())
				return p.VecMov[0];
			else
				return -1;
		}

		// moving up 
		if (p.row - 1 >= 0 && m_visited[p.row - i][p.col] == 0 && !moveTwo)
		{
			// push direction to vector
			p.VecMov.push_back(Object_Direction::Up);
			// push new nudeBfs to queue
			queueManager.push(NudeBfs(p.row - 1, p.col, std::vector<int>(p.VecMov)));
			// pop from vector the last direction
			p.VecMov.pop_back(); 
			// mark the cell
			m_visited[p.row - i][p.col] = 1;
		}

		// moving down 
		if (p.row + i < m_visited.size() &&
			(m_visited[p.row + i][p.col] == 0 || m_visited[p.row + i][p.col] == 2))
		{
			p.VecMov.push_back(Object_Direction::Down);
			queueManager.push(NudeBfs(p.row + 1, p.col, std::vector<int>(p.VecMov)));
			p.VecMov.pop_back();
			m_visited[p.row + i][p.col] = 1;
		}

		// moving left 
		if (p.col - 1 >= 0 &&
			(m_visited[p.row][p.col - i] == 0 || m_visited[p.row][p.col - i] == 2) && !moveTwo)
		{
			p.VecMov.push_back(Object_Direction::Left);
			queueManager.push(NudeBfs(p.row, p.col - 1, std::vector<int>(p.VecMov)));
			p.VecMov.pop_back();
			m_visited[p.row][p.col - i] = 1;
		}

		// moving right 
		if (p.col + i < m_visited[1].size() &&
			(m_visited[p.row][p.col + i] == 0 || m_visited[p.row][p.col + i] == 2) && !moveTwo)
		{
			p.VecMov.push_back(Object_Direction::Right);
			queueManager.push(NudeBfs(p.row, p.col + 1, std::vector<int>(p.VecMov)));
			p.VecMov.pop_back();
			m_visited[p.row][p.col + i] = 1;
		}
	}
	return -1;
}

// return position of objects on mat
//========================================================================
sf::Vector2i MonsterSmart::getPosOnMat(DynamicObject* dObj)
{
	int row, col;

	col = (int)std::round((dObj->getPosition().x - m_size.x / 2u) / m_size.x);
	row = (int)std::round((dObj->getPosition().y - m_size.y / 2u) / m_size.y);

	return sf::Vector2i(row, col);
}

/* build mat 
	Cells that can be reached will be colored with the digit 0.
	All floors will be painted in the number 1. (Can not be reached)
	All other cells will be colored in the number 2.
*/
//========================================================================
void MonsterSmart::buildVisited(const int num)
{
	// build
	m_visited.resize(m_map.size());

	for (int i = 0; i < m_map.size();i++)
		m_visited[i].resize(m_map[i].size());

	// full
	for (size_t i = 0; i < m_map.size(); i++) {
		for (size_t j = 0; j < m_map[i].size(); j++)
		{
			if ((m_map[i][j] == ObjectType::RopesChar || 
				m_map[i][j] == ObjectType::LadderChar) ||
				(i + 1 < m_map.size() && (m_map[i + 1][j] == ObjectType::FloorChar ||
					m_map[i + 1][j] == ObjectType::LadderChar)) && 
					(m_map[i][j] == ObjectType::CoinChar ||
						m_map[i][j] == ObjectType::GiftChar ||
						m_map[i][j] == '\0'))
				m_visited[i][j] = 0;
			else if (m_map[i][j] == ObjectType::FloorChar)
				m_visited[i][j] = 1;
			else
				m_visited[i][j] = num;
		}
	}
}
