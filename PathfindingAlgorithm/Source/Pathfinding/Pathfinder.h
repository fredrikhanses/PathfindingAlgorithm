#pragma once
#include <climits>

struct Node
{
	int m_GCost = INT_MAX;
	int m_FCost = INT_MAX;
	int x = 0;
	int y = 0;
};

class Pathfinder
{
public:
	int FindPath(const int nStartX, const int nStartY,
				 const int nTargetX, const int nTargetY,
				 const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
				 int* pOutBuffer, const int nOutBufferSize);
private:
	int calculateHCost(const int currentX, const int currentY, const int nextX, const int nextY);
	unsigned int getIndex(Node node) const;
	int m_MapWidth = 0;
	int m_MapHeight = 0;
};
