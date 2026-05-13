#include <iostream>
#include "ArrayData.h"
#include "CMyPoint.h"

using namespace std;

int main() {

	ArrayData<CMyPoint> arr;
	arr.addElement(CMyPoint(10, 50));
	arr.addElement(CMyPoint(20, 60));
	cout << arr << endl;

}