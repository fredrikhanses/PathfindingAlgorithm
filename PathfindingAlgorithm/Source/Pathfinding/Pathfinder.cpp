#include "Pathfinder.h"
#include <cmath>
#include <vector>
#include <queue>

unsigned int Pathfinder::getIndex(Node node) const
{
	return node.x + node.y * m_MapWidth;
}

int Pathfinder::calculateHCost(const int currentX, const int currentY, const int nextX, const int nextY)
{
	return std::abs(currentX - nextX) + std::abs(currentY - nextY);
}

int Pathfinder::FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize)
{
	if (nStartX == nTargetX && nStartY == nTargetY)
	{
		return 0;
	}

	m_MapWidth = nMapWidth;
	m_MapHeight = nMapHeight;
	unsigned int mapSize = m_MapWidth * m_MapHeight;

	//f = start -> current node
	//h = current node -> goal
	//g = Sum of f and h

	auto cmp = [](const Node& left, const Node& right) {return (left.m_GCost) > (right.m_GCost); };

	std::vector<bool> visited = std::vector<bool>(mapSize);
	std::vector<Node> parents = std::vector<Node>(mapSize);
	std::vector<bool> walkable = std::vector<bool>(mapSize);

	std::priority_queue<Node, std::vector<Node>, decltype(cmp)> openList(cmp);

	Node startNode;
	startNode.x = nTargetX;
	startNode.y = nTargetY;
	startNode.m_FCost = 0;
	startNode.m_GCost = calculateHCost(nTargetX, nTargetY, nStartX, nStartY);
	openList.push(startNode);

	Node goalNode;
	goalNode.x = nStartX;
	goalNode.y = nStartY;

	const int dirX[] = { 0, 0, -1, 1 };
	const int dirY[] = { -1, 1, 0, 0 };

	for (unsigned int i = 0; i < mapSize; i++)
	{
		if (pMap[i] == 49)
		{
			walkable[i] = true;
		}
	}

	while (!openList.empty())
	{
		const Node current = openList.top();
		openList.pop();

		if (current.x == goalNode.x && current.y == goalNode.y)
		{
			break;
		}

		for (int i = 0; i < 4; ++i)
		{
			const int x = current.x + dirX[i];
			const int y = current.y + dirY[i];

			if (x < 0 || y < 0 || x > m_MapWidth - 1  || y > m_MapHeight - 1)
			{
				continue;
			}

			if (!walkable[x + y * m_MapWidth])
			{
				continue;
			}	

			Node neighbour;
			neighbour.x = x;
			neighbour.y = y;

			const unsigned int neighbourIndex = getIndex(neighbour);

			if (visited[neighbourIndex])
			{
				continue;
			}

			neighbour.m_FCost = current.m_FCost + calculateHCost(current.x, current.y, neighbour.x, neighbour.y);
			neighbour.m_GCost = current.m_FCost + calculateHCost(neighbour.x, neighbour.y, goalNode.x, goalNode.y);

			visited[neighbourIndex] = true;
			parents[neighbourIndex] = current;

			openList.push(neighbour);
		}
	}

	Node currentNode = parents[getIndex(goalNode)];

	int index = 0;
	unsigned int pathSize = 0;
	while ((currentNode.x != nTargetX || currentNode.y != nTargetY) && index < nOutBufferSize)
	{
		pOutBuffer[index] = getIndex(currentNode);
		currentNode = parents[getIndex(currentNode)];
		index++;
		pathSize++;
	}
	if (index < nOutBufferSize)
	{
		pOutBuffer[index] = getIndex(startNode);
		pathSize++;
	}

	if (pathSize > 0 && index < nOutBufferSize)
	{
		return pathSize;
	}
	
	return -1;
}
