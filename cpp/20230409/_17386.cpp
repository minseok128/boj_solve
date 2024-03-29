#include <iostream>
using namespace std;

typedef struct {
	long long x, y;
} Point;

int CCW(Point a, Point b, Point c)
{
	long long s = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	if (s < 0)
		return (-1);
	return (s > 0);
}

int compare(Point *a, Point *b)
{
	return (a->x > b->x || (a->x == b->x && a->y >= b->y));
}

void swap(Point *a, Point *b)
{
	Point tmp;
	if (compare(a, b))
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

int main()
{
	Point a, b, c, d;
	cin >> a.x >> a.y;
	cin >> b.x >> b.y;
	cin >> c.x >> c.y;
	cin >> d.x >> d.y;

	int pa = CCW(a, b, c) * CCW(a, b, d);
	int pb = CCW(c, d, a) * CCW(c, d, b);
	if (pa == 0 && pb == 0)
	{
		swap(&a, &b);	
		swap(&c, &d);
		if (compare(&b, &c) && compare(&d, &a))
			cout << "1\n";
		else
			cout << "0\n";
	}
	else if (pa == -1 && pb == -1)
		cout << "1\n";
	else
		cout << "0\n";
}