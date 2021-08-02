#pragma once

class Map;

class Pathfinder
{
public:
	int FindPath(const int nStartX, const int nStartY,
				 const int nTargetX, const int nTargetY,
				 const unsigned char* pMap, const int nMapWidth, const int nMapHeightX,
				 int* pOutBuffer, const int nOutBufferSize);
private:
	Map* map = nullptr;
};

