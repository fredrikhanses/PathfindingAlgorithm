#pragma once
#include <float.h>

struct Node
{
	float m_GCost = FLT_MAX;
	float m_FCost = FLT_MAX;
	unsigned int x = 0;
	unsigned int y = 0;
};

class Pathfinder
{
public:
	int FindPath(const int nStartX, const int nStartY,
				 const int nTargetX, const int nTargetY,
				 const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
				 int* pOutBuffer, const int nOutBufferSize);
private:
	float calculateHCost(const int currentX, const int currentY, const int nextX, const int nextY);
	unsigned int indexOf(Node node) const;
	unsigned int m_MapWidth = 0;
	unsigned int m_MapHeight = 0;
};
