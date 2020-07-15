#pragma once
struct Point2D {
	long int x;
	long int y;

	long int distanceToInSquare(Point2D other)
	{
		return ((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
	}
};
