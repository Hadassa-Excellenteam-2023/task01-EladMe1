
#include <iostream>
#include "Vector.h"

using namespace std;

int main()
{
	Vector v1(5,3);
	Vector v2(4,3);
	Vector v3 = v2;

	for (int i = 0; i < v1.size(); i++)
		cout << v1[i] << endl;

	if (v1 > v3)
		cout << "v1 is big\n";
	else
		"v3 is big\n";

	if (v2 == v3)
		cout << "equal\n";
	else
		"not equal\n";

	if (v1 != v3)
		cout << "not equal\n";
	else
		"equal\n";

	if (v2.empty())
		cout << "empty\n";
	else
		"not empty\n";


	return 0;
}