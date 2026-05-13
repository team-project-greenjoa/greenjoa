#pragma once
#include <iostream>
using namespace std;

class CMyPoint
{
private:
	int x, y;
public:
	CMyPoint() = default;
	~CMyPoint() = default;
	CMyPoint(const int& x, const int& y) : x(x), y(y) {}
	int getX() const { return x; }
	int getY() const { return y; }
	bool operator< (const CMyPoint& pt) const;
	bool operator> (const CMyPoint& pt) const;
};

ostream& operator<<(ostream& out, const CMyPoint& point);
