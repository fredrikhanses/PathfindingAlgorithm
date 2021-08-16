#include <random>
#include <time.h>
#include <iostream>
#include <chrono>
#include "Source/Pathfinding/Pathfinder.h"

int main()
{
	const bool drawMap = true;

	const int mapSize = 900;
	const int width = 25;
	const int height = 37;
	const int outBufferSize = 100;

	const unsigned int lastPositionCoordinateX = width - 1;
	const unsigned int lastPositionCoordinateY = height - 1;

	int* outBuffer = new int[outBufferSize];

	const unsigned char walkable = '1';
	const unsigned char impassable = '0';
	const unsigned char path = '-';
	const unsigned char start = '~';
	const unsigned char goal = '*';
	const unsigned int walkableRatio = 4;
	unsigned int numberOfImpassables = 0;
	unsigned int numberOfWalkables = 0;

	unsigned char* pMap = new unsigned char[mapSize];
	std::srand((unsigned int)time(NULL));

	unsigned int startX = std::rand() * lastPositionCoordinateX / RAND_MAX;
	unsigned int startY = std::rand() * lastPositionCoordinateY / RAND_MAX;
	unsigned int goalX = std::rand() * lastPositionCoordinateX / RAND_MAX;
	unsigned int goalY = std::rand() * lastPositionCoordinateY / RAND_MAX;

	for (unsigned int index = 0; index < mapSize; index++)
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
		pMap[startX + startY * width] = walkable;
		pMap[goalX + goalY * width] = walkable;
	}

	Pathfinder* pathfinder = new Pathfinder();
	int pathLength = 0;

	auto startClock = std::chrono::high_resolution_clock::now();
	pathLength = pathfinder->findPath(startX, startY, goalX, goalY, pMap, width, height, outBuffer, outBufferSize);
	auto stopClock = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = stopClock - startClock;

	if (drawMap)
	{
		if (pathLength > 0 && pathLength <= outBufferSize)
		{
			std::cout << "PathIndices: ";
			for (int index = 0; index < pathLength; index++)
			{
				std::cout << " " << outBuffer[index];
				if(index != pathLength - 1)
				{
					std::cout << ",";
				}
				pMap[outBuffer[index]] = path;
			}
		}

		pMap[startX + startY * width] = start;
		pMap[goalX + goalY * width] = goal;
		std::cout << std::endl;

		for (unsigned int index = 0; index < mapSize; index++)
		{
			std::cout << " | " << pMap[index];
			if (!((index + 1) % width))
			{
				std::cout << " | " << std::endl;
			}
		}
	}

	std::cout << "0's: " << numberOfImpassables << std::endl;
	std::cout << "1's: " << numberOfWalkables << std::endl;
	std::cout << "Start ~ : (" << startX << ", " << startY << ") | Index: " << startX + startY * width << std::endl;
	std::cout << "Goal  * : (" << goalX << ", " << goalY << ") | Index: " << goalX + goalY * width << std::endl;
	std::cout << "PathSize: " << pathLength << std::endl;
	std::cout << "Time: " << elapsed.count() << " s" << std::endl;
	std::cout << "Nodes checked: " << pathfinder->getNodesChecked() << std::endl;

	delete pathfinder;
	delete[] pMap;
	delete[] outBuffer;

	return 0;
}