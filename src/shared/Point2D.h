#pragma once
struct Point2D {
	int x;
	int y;

	int distanceToInSquare(Point2D other)
	{
		return ((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
	}
};
