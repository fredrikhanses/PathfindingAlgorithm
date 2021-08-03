#include <iostream>
#include "Source/Pathfinding/Pathfinder.h"

int main()
{
	const bool drawMap = true;

	const int nOutBufferSize = 100; // 4 - 81 000 000
	const unsigned int widthHeight = (unsigned int)std::sqrtf(nOutBufferSize);
	const unsigned int lastPositionCoordinate = widthHeight - 1;
	int* pOutBuffer = new int[nOutBufferSize];

	const unsigned int walkable = 49;
	const unsigned int impassable = 48;
	const unsigned int path = 45;
	const unsigned int walkableRatio = 5; // 2 - INT_MAX
	unsigned int numberOfImpassables = 0;
	unsigned int numberOfWalkables = 0;

	Pathfinder* pathfinder = new Pathfinder();
	int pathLength = 0;

	unsigned char* pMap = new unsigned char[nOutBufferSize];
	std::srand((unsigned int)time(NULL));

	for (unsigned int index = 0; index < nOutBufferSize; index++)
	{
		unsigned int randomNumber = std::rand() * walkableRatio / RAND_MAX + impassable;
		if (randomNumber > walkable)
		{
			randomNumber = walkable;
		}
		if (randomNumber == impassable)
		{
			numberOfImpassables++;
		}
		else
		{
			numberOfWalkables++;
		}
		pMap[index] = (unsigned char)randomNumber;
		pMap[0] = walkable;
		pMap[nOutBufferSize - 1] = walkable;

		if (drawMap)
		{
			std::cout << " | " << pMap[index];
			if (!((index + 1) % widthHeight))
			{
				std::cout << " | " << std::endl;
			}
		}
	}

	pathLength = pathfinder->findPath(0, 0, lastPositionCoordinate, lastPositionCoordinate, pMap, widthHeight, widthHeight, pOutBuffer, nOutBufferSize);

	if (drawMap && pathLength > 0)
	{
		for (int index = 0; index < pathLength; index++)
		{
			std::cout << " " << pOutBuffer[index] << ",";
			if (!((index + 1) % widthHeight))
			{
				std::cout << std::endl;
			}

			pMap[pOutBuffer[index]] = path;
		}
		pMap[0] = path;
		std::cout << std::endl;

		for (unsigned int index = 0; index < nOutBufferSize; index++)
		{
			std::cout << " | " << pMap[index];
			if (!((index + 1) % widthHeight))
			{
				std::cout << " | " << std::endl;
			}
		}
	}

	std::cout << "0s: " << numberOfImpassables << std::endl;
	std::cout << "1s: " << numberOfWalkables << std::endl;
	std::cout << "PathSize: " << pathLength << std::endl;

	//int in = 0;	
	//std::cin >> in;

	delete pathfinder;
	delete[] pMap;
	delete[] pOutBuffer;

	return 0;
}
