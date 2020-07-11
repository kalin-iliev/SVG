#pragma once
struct Point2D {
	long int x;
	long int y;
	Point2D(long int x, long int y) {
		this->x = x;
		this->y = y;
	}
	bool operator ==(const Point2D& other) {
		return this->x == other.x && this->y == other.y;
	}

	long int distanceToInSquare(Point2D other)
	{
		return ((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
	}
};
