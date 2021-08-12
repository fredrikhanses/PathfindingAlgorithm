#include <cmath>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

// main REMOVE
#include <random>
#include <time.h>

// class REMOVE
class ParadoxPathfinder
{
public:
	int m_MapWidth = 0;
	int m_MapHeight = 0;

	unsigned char m_Walkable = '1';
	unsigned char m_Impassable = '0';

	struct Node
	{
		int m_GCost = INT_MAX;
		int m_FCost = INT_MAX;
		int x = 0;
		int y = 0;
	};

	unsigned int GetIndex(Node node)
	{
		return node.x + node.y * m_MapWidth;
	}

	int CalculateHCost(const int currentX, const int currentY, const int nextX, const int nextY)
	{
		return std::abs(currentX - nextX) + std::abs(currentY - nextY);
	}

	int FindPath(int nStartX, int nStartY, int nTargetX, int nTargetY, unsigned char const* pMap, int nMapWidth, int nMapHeight, int* pOutBuffer, int nOutBufferSize)
	{
		if (nStartX == nTargetX && nStartY == nTargetY)
		{
			return 0;
		}
		//else if(nOutBufferSize < (nMapWidth + nMapHeight - 2) || nOutBufferSize == 0)
		//{
		//	return (nMapWidth + nMapHeight - 2);
		//}

		m_MapWidth = nMapWidth;
		m_MapHeight = nMapHeight;
		unsigned int mapSize = m_MapWidth * m_MapHeight;

		std::vector<Node> parents = std::vector<Node>(mapSize);
		char* walkable = new char[mapSize];
		std::memcpy(walkable, pMap, sizeof(char) * mapSize);
		auto comparator = [](const Node& left, const Node& right) { return (left.m_GCost) > (right.m_GCost); };
		std::priority_queue<Node, std::vector<Node>, decltype(comparator)> openList(comparator);

		Node startNode;
		startNode.x = nTargetX;
		startNode.y = nTargetY;
		startNode.m_FCost = 0;
		startNode.m_GCost = CalculateHCost(nTargetX, nTargetY, nStartX, nStartY);
		openList.push(startNode);

		Node goalNode;
		goalNode.x = nStartX;
		goalNode.y = nStartY;

		const int dirX[] = { 0, 0, -1, 1 };
		const int dirY[] = { -1, 1, 0, 0 };

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

				if (x < 0 || y < 0 || x > m_MapWidth - 1 || y > m_MapHeight - 1)
				{
					continue;
				}

				if (walkable[x + y * m_MapWidth] != m_Walkable)
				{
					continue;
				}

				Node neighbour;
				neighbour.x = x;
				neighbour.y = y;

				const unsigned int neighbourIndex = GetIndex(neighbour);

				if (walkable[neighbourIndex] != m_Walkable)
				{
					continue;
				}

				neighbour.m_FCost = current.m_FCost + CalculateHCost(current.x, current.y, neighbour.x, neighbour.y);
				neighbour.m_GCost = current.m_FCost + CalculateHCost(neighbour.x, neighbour.y, goalNode.x, goalNode.y);

				walkable[neighbourIndex] = m_Impassable;
				parents[neighbourIndex] = current;

				openList.push(neighbour);
			}
		}

		delete[] walkable;

		int index = 0;
		unsigned int pathSize = 0;
		int* indices = new int[nOutBufferSize];
		Node currentNode = parents[GetIndex(goalNode)];
		while ((currentNode.x != nTargetX || currentNode.y != nTargetY) && index < nOutBufferSize)
		{
			indices[index] = GetIndex(currentNode);
			currentNode = parents[GetIndex(currentNode)];
			index++;
			pathSize++;
		} 

		if (index < nOutBufferSize)
		{
			std::memcpy(pOutBuffer, indices, sizeof(int) * nOutBufferSize);
			pOutBuffer[index] = GetIndex(startNode);
		}

		if (pathSize > 0 && index < nOutBufferSize)
		{
			pathSize++;
			delete[] indices;
			return pathSize;
		}

		delete[] indices;
		return -1;
	}
// class REMOVE
};

// main REMOVE
//int main()
//{
//	const unsigned char walkable = '1';
//	const unsigned char impassable = '0';
//	const unsigned char start = 'X';
//	const unsigned char path = '-';
//
//	const bool drawMap = true;
//	const bool randomMap = true;
//	const int nOutBufferSize = 2;
//	const unsigned int randomMapSize = 4;
//	const unsigned int walkableRatio = 5;
//	
//	unsigned int mapSize = randomMapSize;
//	unsigned int width = 2;
//	unsigned int height = 2;
//
//	unsigned int startX = 0;
//	unsigned int startY = 0;
//	unsigned int goalX = width - 1;
//	unsigned int goalY = height - 1;
//
//	int* pOutBuffer = new int[nOutBufferSize];
//	unsigned char* pMap = new unsigned char[randomMapSize];
//	int pathLength = 0;
//	std::srand((unsigned int)time(NULL));
//
//	if (randomMap)
//	{
//		for (unsigned int index = 0; index < randomMapSize; index++)
//		{
//			unsigned int randomNumber = std::rand() * walkableRatio / RAND_MAX + impassable;
//			if (randomNumber > walkable)
//			{
//				randomNumber = walkable;
//			}
//			pMap[index] = (unsigned char)randomNumber;
//			pMap[startX + startY * width] = walkable;
//			pMap[goalX + goalY * width] = walkable;
//		}
//	}
//	else
//	{
//		mapSize = 9;
//		width = 3;
//		height = 3;
//		startX = 2;
//		startY = 0;
//		goalX = 0;
//		goalY = 2;
//		pMap[0] = '0';
//		pMap[1] = '0';
//		pMap[2] = '1';
//		pMap[3] = '1';
//		pMap[4] = '1';
//		pMap[5] = '1';
//		pMap[6] = '1';
//		pMap[7] = '0';
//		pMap[8] = '1';
//	}
//
//	ParadoxPathfinder* pathfinder = new ParadoxPathfinder();
//	pathLength = pathfinder->FindPath(startX, startY, goalX, goalY, pMap, width, height, pOutBuffer, nOutBufferSize);
//
//	if (drawMap)
//	{
//		if (pathLength > 0 && pathLength <= nOutBufferSize)
//		{
//			for (int index = 0; index < pathLength; index++)
//			{
//				std::cout << " " << pOutBuffer[index] << ",";
//				if (!((index + 1) % 10))
//				{
//					std::cout << std::endl;
//				}
//				pMap[pOutBuffer[index]] = path;
//			}
//			std::cout << std::endl;
//		}
//
//		pMap[startX + startY * width] = start;
//		
//		for (unsigned int index = 0; index < mapSize; index++)
//		{
//			std::cout << " | " << pMap[index];
//			if (!((index + 1) % width))
//			{
//				std::cout << " | " << std::endl;
//			}
//		}
//	}
//
//	std::cout << std::endl << " " << pathLength << std::endl;
//
//	delete pathfinder;
//	delete[] pMap;
//	delete[] pOutBuffer;
//
//	return 0;
//}
