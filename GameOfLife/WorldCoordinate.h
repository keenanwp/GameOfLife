#ifndef WORLDCOORDINATE_H
#define WORLDCOORDINATE_H

#include <functional>

struct WorldCoordinate
{
	long long x;
	long long y;

	bool operator==(const WorldCoordinate& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
};

struct WorldCoordinateHash
{
	size_t operator()(const WorldCoordinate& coord) const
	{
		size_t h1 = std::hash<long long>{}(coord.x);
		size_t h2 = std::hash<long long>{}(coord.y);
		return h1 ^ (h2 << 1);
	}
};

#endif // !WORLDCOORDINATE_H

