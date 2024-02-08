// points.cpp

/*

Design a class for representing (x, y) points. Think about:

- The different kinds of constructors you might want. For example:

    Point a(4, -5);
    Point b(c); // copy constructor
    Point origin; // default constructor: (0, 0)

- What should be public/private.

  In this particular case, it is not clear if any private members are need.
  While you could make setters/getters for x and y, it seems they'll do the same
  as if they were public.

- Should the class be mutable or immutable?

  This is a tricky choice. There are pros and cons for both choices. Lets go with 
  immutable for now.

- What other helper methods you might want. Have methods to at least:

  - Print the point.

  - Compute the distance between two points.

  - Test if two points are equal.

  - Add two points, e.g. (1, 2) + (3, 4) = (4, 6).

- Write a function (not a method!) with this header to help test your code:

     Point furthest_from_origin(const vector<Point> &points)

*/

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Point
{
    //
    // Making x and y const means that after they're initialized they cannot be
    // changed. You must use an initialization list to initialize them. If you
    // try to assign them with = in the body of the constructor you'll get an
    // error saying that you're trying to assign to a const member.
    //
    const int x;
    const int y;

    Point(int x, int y)
        : x(x), y(y)
    {
    }

    //
    // copy constructor
    //
    Point(const Point &other)
        : x(other.x), y(other.y)
    {
    }

    //
    // default constructor (no parameters)
    //
    Point()
        : x(0), y(0)
    {
    }

    string to_string() const
    {
        string result = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
        return result;
    }

    double dist_to(const Point &other) const
    {
        int dx = x - other.x;
        int dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }

    bool same_as(const Point &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator==(const Point &other) const
    {
        return same_as(other);
    }

    bool operator!=(const Point &other) const
    {
        return !same_as(other);
    }

    //
    // operator+ lets you add to points using +
    // e.g. Point(1, 2) + Point(3, 4) == Point(4, 6)
    //
    Point operator+(const Point &other) const
    {
        return Point(x + other.x, y + other.y);
    }

}; // struct Point

//
// Return a copy of the point furthest from (0, 0), the origin.
//
Point furthest_from_origin(const vector<Point> &points)
{
    assert(points.size() > 0);

    Point origin;
    int index_of_furthest = 0;
    Point first = points[index_of_furthest];
    double dist_to_furthest = first.dist_to(origin);

    for (int i = 1; i < points.size(); i++)
    {
        double dist_to_current = points[i].dist_to(origin);
        if (dist_to_current > dist_to_furthest)
        {
            index_of_furthest = i;
            dist_to_furthest = dist_to_current;
        }
    }
    return points[index_of_furthest];
}

void test_Point()
{
    cout << "test_Point called ..." << endl;
    Point a(4, -5);
    assert(a.x == 4);
    assert(a.y == -5);

    Point b(a); // copy constructor
    assert(b.x == 4);
    assert(b.y == -5);

    Point origin; // default constructor: (0, 0)
    assert(origin.x == 0);
    assert(origin.y == 0);

    // origin.x = 5; // compile-time error: assignment of read-only member 'Point::x'

    assert(a.to_string() == "(4, -5)");
    assert(b.to_string() == "(4, -5)");
    assert(origin.to_string() == "(0, 0)");

    assert(a.dist_to(b) == 0);
    assert(b.dist_to(a) == 0);
    assert(a.dist_to(a) == 0);
    assert(a.dist_to(origin) == 6.4031242374328485);
    assert(origin.dist_to(Point(3, 0)) == 3);

    assert(a.same_as(a));
    assert(a.same_as(b));
    assert(b.same_as(a));
    assert(!a.same_as(origin));
    assert(!origin.same_as(a));

    assert(a == a);
    assert(a == b);
    assert(b == a);
    assert(a != origin);
    assert(origin != a);

    assert(Point(1, 2) + Point(3, 4) == Point(4, 6));
    assert(Point(3, 4) + Point(1, 2) == Point(4, 6));
    assert(origin + a == a);
    assert(a + origin == a);
    assert(origin + origin == origin);

    vector<Point> points = {Point(1, 2), origin, Point(3, 4), Point(5, -6)};
    assert(furthest_from_origin(points) == Point(5, -6));

    cout << "test_Point done." << endl;
}

void test_Point_pointers()
{
    cout << "test_Point_pointers called ..." << endl;
    Point a(4, -5);
    Point *p = &a;

    assert(p->x == 4);
    assert(p->y == -5);
    assert(p->to_string() == "(4, -5)");

    Point *pt = new Point(1, 2);
    assert(pt->x == 1);
    assert(pt->y == 2);
    assert(pt->to_string() == "(1, 2)");

    delete pt;

    cout << "test_Point_pointers done." << endl;
}

int main()
{
    test_Point();
    test_Point_pointers();
} // main
