#include "WorldSimulator.h"

#include <iostream>


WorldSimulator::WorldSimulator()
{
	ptrWorld = new World();
}

WorldSimulator::WorldSimulator(const WorldSimulator & other)
{
	ptrWorld = new World(*other.ptrWorld);
}

WorldSimulator::~WorldSimulator()
{
	delete ptrWorld;
}

WorldSimulator & WorldSimulator::operator=(const WorldSimulator & rhs)
{
	World* orig = ptrWorld;
	ptrWorld = new World(*rhs.ptrWorld);
	delete orig;

	return *this;
}

void WorldSimulator::Start(unsigned int maxIterations)
{
	if (ptrWorld->IsEmpty())
	{
		std::cout << "The world is already dead" << std::endl;
		return;
	}

	PrintWorld();

	for (unsigned int i = 0; i < maxIterations; ++i)
	{
		ptrWorld->Update();

		if (ptrWorld->IsEmpty())
		{
			std::cout << "The world ends after " << i + 1 << " iterations." << std::endl;
			break;
		}

		PrintWorld();
	}
}

void WorldSimulator::PrintWorld() const
{
	for (auto it = ptrWorld->LiveCellsBegin(); it != ptrWorld->LiveCellsEnd(); ++it)
		std::cout << "(" << it->x << ", " << it->y << ")" << std::endl;

	std::cout << "==========" << std::endl;
}
