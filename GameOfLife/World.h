#ifndef WORLD_H
#define WORLD_H

#include "WorldCoordinate.h"

#include <iostream>
#include <unordered_set>
#include <unordered_map>

class World
{
public:
	template<class charT, class traits>
	bool ReadCoordinateInput(std::basic_istream<charT, traits>& in);

	void Update();

	bool IsEmpty() const { return liveCells.empty(); }
	bool IsCellAlive(const WorldCoordinate& coord) const { return liveCells.count(coord) > 0; }

	typedef std::unordered_set<WorldCoordinate, WorldCoordinateHash> WorldCoordinateSet;
	WorldCoordinateSet::const_iterator LiveCellsBegin() const { return liveCells.cbegin(); }
	WorldCoordinateSet::const_iterator LiveCellsEnd() const { return liveCells.cend(); }

private:
	WorldCoordinateSet liveCells;
	std::unordered_map<WorldCoordinate, char, WorldCoordinateHash> deadNeigbors;
};

template<class charT, class traits>
inline bool World::ReadCoordinateInput(std::basic_istream<charT, traits>& in)
{
	WorldCoordinate coord;
	while (in >> coord.x >> coord.y)
		liveCells.insert(coord);

	if (in.eof())
	{
		if (!IsEmpty())
			return true;

		std::cerr << "Empty coordinate input!" << std::endl;
	}

	if (in.fail())
		std::cerr << "Error reading coordinate input!  Input should be space separated pairs of integers, e.g. -7 9" << std::endl;

	if(in.bad())
		std::cerr << "Error reading coordinate input!  Corrupt input stream" << std::endl;

	return false;
}

#endif // !WORLD_H
