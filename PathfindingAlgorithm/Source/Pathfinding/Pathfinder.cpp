#include "Pathfinder.h"
#include <cmath>
#include <vector>
#include <queue>
#include <cstring>

Pathfinder::Pathfinder(unsigned int nodesChecked) : m_NodesChecked(nodesChecked){}

int Pathfinder::findPath(const int startX, const int startY, const int targetX, 
						 const int targetY, unsigned char const* map, const int mapWidth, 
						 const int mapHeight, int* outBuffer, const int outBufferSize)
{
	if (startX == targetX && startY == targetY)
	{
		return 0;
	}

	const unsigned char walkableChar = '1';
	const unsigned char impassableChar = '0';
	bool pathFound = false;
	const int directionsX[] = { 0, 0, -1, 1 };
	const int directionsY[] = { -1, 1, 0, 0 };
	const unsigned int mapSize = mapWidth * mapHeight;

	char* walkableNodes = new char[mapSize];
	std::memcpy(walkableNodes, map, sizeof(char) * mapSize);

	std::vector<Node> parentNodes = std::vector<Node>(mapSize);

	auto comparator = [](const Node& left, const Node& right) { return (left.m_GCost) > (right.m_GCost); };
	std::priority_queue<Node, std::vector<Node>, decltype(comparator)> nodesToCheck(comparator);

	const Node startNode(targetX, targetY, 0, calculateHCost(targetX, targetY, startX, startY));
	nodesToCheck.push(startNode);

	const Node goalNode(startX, startY);

	while (!nodesToCheck.empty())
	{
		const Node currentNode = nodesToCheck.top();
		nodesToCheck.pop();

		if (currentNode.m_X == goalNode.m_X && currentNode.m_Y == goalNode.m_Y)
		{
			pathFound = true;
			break;
		}

		for (int i = 0; i < 4; ++i)
		{
			const int x = currentNode.m_X + directionsX[i];
			const int y = currentNode.m_Y + directionsY[i];

			if (x < 0 || y < 0 || x > mapWidth - 1 || y > mapHeight - 1)
			{
				continue;
			}

			if (walkableNodes[x + y * mapWidth] != walkableChar)
			{
				continue;
			}

			Node neighbourNode;
			neighbourNode.m_X = x;
			neighbourNode.m_Y = y;

			const unsigned int neighbourIndex = getIndex(neighbourNode, mapWidth);

			if (walkableNodes[neighbourIndex] != walkableChar)
			{
				continue;
			}

			neighbourNode.m_FCost = currentNode.m_FCost + calculateHCost(currentNode.m_X, currentNode.m_Y, neighbourNode.m_X, neighbourNode.m_Y);
			neighbourNode.m_GCost = currentNode.m_FCost + calculateHCost(neighbourNode.m_X, neighbourNode.m_Y, goalNode.m_X, goalNode.m_Y);

			walkableNodes[neighbourIndex] = impassableChar;
			parentNodes[neighbourIndex] = currentNode;

			nodesToCheck.push(neighbourNode);
			m_NodesChecked++;
		}
	}

	delete[] walkableNodes;

	return returnPath(parentNodes, startNode, goalNode, pathFound, mapWidth, outBuffer, outBufferSize, targetX, targetY);
}

unsigned int Pathfinder::calculateHCost(const int& currentX, const int& currentY, 
										const int& nextX, const int& nextY) const
{
	return std::abs(currentX - nextX) + std::abs(currentY - nextY);
}

unsigned int Pathfinder::getIndex(const Node& node, const int& mapWidth) const
{
	return node.m_X + node.m_Y * mapWidth;
}

int Pathfinder::returnPath(const std::vector<Node>& parents, const Node& startNode, 
							const Node& goalNode, const bool& pathFound, 
							const int& mapWidth, int* outBuffer, const int& outBufferSize, 
							const int& targetX, const int& targetY) const
{
	int pathSize = -1;

	if (pathFound)
	{
		pathSize = 0;
		int index = 0;
		bool increaseBuffer = false;
		int* indices = new int[outBufferSize];
		Node currentNode = parents[getIndex(goalNode, mapWidth)];
		while (currentNode.m_X != targetX || currentNode.m_Y != targetY)
		{
			if (index < outBufferSize)
			{
				indices[index] = getIndex(currentNode, mapWidth);
			}
			currentNode = parents[getIndex(currentNode, mapWidth)];
			index++;
			pathSize++;
		}

		pathSize++;

		if (index < outBufferSize)
		{
			indices[index] = getIndex(startNode, mapWidth);
		}

		if (pathSize > outBufferSize)
		{
			increaseBuffer = true;
		}

		if (!increaseBuffer)
		{
			std::memcpy(outBuffer, indices, sizeof(int) * outBufferSize);
		}

		delete[] indices;
	}

	return pathSize;
}
