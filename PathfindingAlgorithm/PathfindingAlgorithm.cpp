#include "Pathfinding/Pathfinder.h"

int main()
{
    const int nOutBufferSize = 12;
    unsigned char pMap[] = {1, 1, 1, 1};
    int pOutBuffer[nOutBufferSize];
    Pathfinder* pathfinder = new Pathfinder();
    return pathfinder->FindPath(0, 0, 1, 0, pMap, 2, 2, pOutBuffer, nOutBufferSize);
}
