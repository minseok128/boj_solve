#include <iostream>
#include <vector>
using namespace std;

typedef struct
{
	long long x, y;
} Point;

typedef struct
{
	Point p1, p2;
} Line;

int CCW(Point a, Point b, Point c)
{
	long long s = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	if (s < 0)
		return (-1);
	return (s > 0);
}

int compare(Point *a, Point *b)
{
	if (a->x > b->x)
	{
		return (1);
	}
	else if (a->x == b->x)
	{
		if (a->y > b->y)
			return (1);
		if (a->y == b->y)
			return (2);
	}
	return (0);
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

double cross(Line *l1, Line *l2)
{
	Point a = l1->p1;
	Point b = l1->p2;
	Point c = l2->p1;
	Point d = l2->p2;

	int p1 = CCW(a, b, c) * CCW(a, b, d);
	int p2 = CCW(c, d, a) * CCW(c, d, b);
	if (compare(&b, &c) == 2 || compare(&a, &d) == 2)
		return (0.5);
	if (compare(&a, &c) == 2)
	{
		if (a.x == b.x && a.x == d.x && b.x == d.x)
			return (5);
		if ((b.y - a.y) * (d.x - a.x) == (d.y - a.y) * (b.x - a.x))
			return (5);
		return (0.5);
	}
	if (compare(&b, &d) == 2)
	{
		if ((b.y - a.y) * (b.x - c.x) == (b.y - c.y) * (b.x - a.x))
			return (5);
		return (0.5);
	}
	if (p1 == 0 && p2 == 0)
	{
		if (compare(&b, &c) && compare(&d, &a))
			return (5);
		else
			return (0);
	}
	else if (CCW(a, b, c) == 0)
	{
		if (compare(&c, &a) && compare(&b, &c))
			return (0.5);
		else
			return (0);
	}
	else if (CCW(a, b, d) == 0)
	{
		if (compare(&d, &a) && compare(&b, &d))
			return (0.5);
		else
			return (0);
	}
	else if (CCW(c, d, a) == 0)
	{
		if (compare(&a, &c) && compare(&d, &a))
			return (1);
		else
			return (0);
	}
	else if (CCW(c, d, b) == 0)
	{
		if (compare(&b, &c) && compare(&d, &b))
			return (1);
		else
			return (0);
	}
	else if (p1 == -1 && p2 == -1)
		return (1);
	else
		return (0);
}

int main()
{
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(0);
	int N, xl, yt, xr, yb;
	double result;
	Line l1, R[4];

	for (cin >> N; N > 0; N--)
	{
		cin >> xl >> yb >> xr >> yt;
		R[0].p1.x = R[0].p2.x = R[1].p1.x = R[3].p1.x = xl;
		R[0].p1.y = R[1].p1.y = R[1].p2.y = R[2].p1.y = yb;
		R[1].p2.x = R[2].p1.x = R[2].p2.x = R[3].p2.x = xr;
		R[2].p2.y = R[0].p2.y = R[3].p1.y = R[3].p2.y = yt;

		cin >> l1.p1.x >> l1.p1.y >> l1.p2.x >> l1.p2.y;
		swap(&(l1.p1), &(l1.p2));

		result = 0;
		for (int i = 0; i < 4; i++)
			result += cross(&l1, &(R[i]));
		cout <<  (result > 3 ? 4 : result) << "\n";
	}
}