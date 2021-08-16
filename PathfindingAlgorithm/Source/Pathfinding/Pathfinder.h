#pragma once
#include <climits>
#include <vector>

struct Node
{
	Node(const int x = 0, const int y = 0, const int fCost = INT_MAX, const int gCost = INT_MAX)
	{
		m_X = x;
		m_Y = y;
		m_FCost = fCost;
		m_GCost = gCost;
	}
	int m_X = 0;
	int m_Y = 0;
	int m_FCost = INT_MAX;
	int m_GCost = INT_MAX;
};

class Pathfinder
{
public:
	Pathfinder(const unsigned int nodesChecked = 0);
	int findPath(const int startX, const int startY, const int targetX, 
				 const int targetY, const unsigned char* map, const int mapWidth, 
				 const int mapHeight, int* outBuffer, const int outBufferSize);
	unsigned int getNodesChecked() { return m_NodesChecked; }

private:
	int returnPath(const std::vector<Node>& parents, const Node& startNode, 
					const Node& goalNode, const bool& pathFound, 
					const int& mapWidth, int* outBuffer, const int& outBufferSize, 
					const int& targetX, const int& targetY) const;
	unsigned int calculateHCost(const int& currentX, const int& currentY, 
								const int& nextX, const int& nextY) const;
	unsigned int getIndex(const Node& node, const int& mapWidth) const;
	unsigned int m_NodesChecked;
};
