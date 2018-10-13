#include "World.h"

#include <list>
#include <numeric>


void World::Update()
{
	std::list<WorldCoordinate> dyingCells;

	for (auto liveIt = liveCells.cbegin(); liveIt != liveCells.cend(); ++liveIt)
	{
		long long xCoord = liveIt->x;
		long long yCoord = liveIt->y;

		char minI = xCoord == std::numeric_limits<long long>::min() ? 0 : -1;
		char maxI = xCoord == std::numeric_limits<long long>::max() ? 0 : 1;
		char minJ = yCoord == std::numeric_limits<long long>::min() ? 0 : -1;
		char maxJ = yCoord == std::numeric_limits<long long>::max() ? 0 : 1;

		WorldCoordinate neighbor;
		char liveNeighbors = 0;
		for (char i = minI; i <= maxI; ++i)
		{
			for (char j = minJ; j <= maxJ; ++j)
			{
				if (i == 0 && j == 0)
					continue;

				neighbor.x = xCoord + i;
				neighbor.y = yCoord + j;

				if (liveCells.count(neighbor) > 0)
					liveNeighbors++;
				else
					deadNeigbors[neighbor]++;
			}
		}

		if (liveNeighbors < 2 || liveNeighbors > 3)
			dyingCells.push_back(*liveIt);
	}

	for (auto dieIt = dyingCells.cbegin(); dieIt != dyingCells.cend(); ++dieIt)\
		liveCells.erase(*dieIt);

	std::list<WorldCoordinate> spawnedCells;
	std::list<WorldCoordinate> removedCells;

	for (auto deadIt = deadNeigbors.begin(); deadIt != deadNeigbors.end(); ++deadIt)
	{
		if (deadIt->second == 3)
			spawnedCells.push_back(deadIt->first);
		else if (deadIt->second == 0)
			removedCells.push_back(deadIt->first);

		deadIt->second = 0;
	}

	for (auto removedIt = removedCells.cbegin(); removedIt != removedCells.cend(); ++removedIt)
		deadNeigbors.erase(*removedIt);

	liveCells.insert(spawnedCells.cbegin(), spawnedCells.cend());
}
