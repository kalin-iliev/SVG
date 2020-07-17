#ifndef POINT_2D_HEADER_INCLUDED
#define POINT_2D_HEADER_INCLUDED

struct Point2D {
	int x;
	int y;

	int distanceToInSquare(Point2D other)
	{
		return ((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
	}
};

#endif