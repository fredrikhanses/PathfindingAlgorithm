#include <iostream>
#include "Source/Pathfinding/Pathfinder.h"

int main()
{
    const int nOutBufferSize = 2;
    unsigned char pMap[] = { 1, 1, 1, 1,
                             1, 0, 0, 1, 
                             1, 0, 1, 1, 
                             1, 1, 1, 1 };
    int pOutBuffer[nOutBufferSize];
    Pathfinder* pathfinder = new Pathfinder();
    int pathLength = pathfinder->FindPath(0, 0, 2, 2, pMap, 4, 4, pOutBuffer, nOutBufferSize);
    delete pathfinder;
    std::cout << "PathSize: " << pathLength << std::endl;
    for (unsigned int index = 0; index < nOutBufferSize; index++)
    {
		std::cout << "Index: " << pOutBuffer[index] << std::endl;
    }
    return 0;
}
