#include "Pathfinder.h"

int Pathfinder::FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeightX, int* pOutBuffer, const int nOutBufferSize)
{
	if (nStartX == nTargetX && nStartY == nTargetY)
	{
		return 0;
	}
	return -1;
}
