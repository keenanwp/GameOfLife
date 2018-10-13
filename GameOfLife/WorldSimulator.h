#ifndef WORLDSIMULATOR_H
#define WORLDSIMULATOR_H

#include "World.h"

#include <iosfwd>

class WorldSimulator
{
public:
	WorldSimulator();
	WorldSimulator(const WorldSimulator& other);
	~WorldSimulator();

	WorldSimulator& operator=(const WorldSimulator& rhs);

	template<class charT, class traits>
	bool ReadInput(std::basic_istream<charT, traits>& in);

	void Start(unsigned int maxIterations = 32);
	void PrintWorld() const;

private:
	World* ptrWorld;
};

template<class charT, class traits>
inline bool WorldSimulator::ReadInput(std::basic_istream<charT, traits>& in)
{
	return ptrWorld->ReadCoordinateInput(in);
}

#endif // !WORLDSIMULATOR_H
