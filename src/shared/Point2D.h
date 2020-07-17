#ifndef POINT_2D_HEADER_INCLUDED
#define POINT_2D_HEADER_INCLUDED

struct Point2D
{
	int x;
	int y;

	int squaredDistanceTo(Point2D other)
	{
		return ((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
	}

    Point2D(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Point2D& operator+=(const Point2D other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    Point2D operator+(const Point2D other) const
    {
        Point2D result(*this);
        result.x += other.x;
        result.y += other.y;
        return result;
    }
};

#endif