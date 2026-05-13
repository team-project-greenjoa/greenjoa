#include "CMyPoint.h"
#include <iostream>
using namespace std;

ostream& operator<<(ostream& out, const CMyPoint& point) {
	out << point.getX() << "," << point.getY() << endl;
	return out;
}

bool CMyPoint::operator< (const CMyPoint& pt) const {
	if (x < pt.getX()) return true;
	return false;
}

bool CMyPoint::operator> (const CMyPoint& pt) const {
	if (x > pt.getX()) return true;
	return false;
}