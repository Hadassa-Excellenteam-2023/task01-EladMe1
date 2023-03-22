
#include <iostream>
#include "Vector.h"



int main()
{
	Vector v1(5,3);
	Vector v2(4,3);
	Vector v3 = v2;

	for (int i = 0; i < v1.size(); i++)
		std::cout << v1[i] << std::endl;

	if (v1 > v3)
		std::cout << "v1 is big\n";
	else
		std::cout << "v3 is big\n";

	if (v2 == v3)
		std::cout << "equal\n";
	else
		std::cout << "not equal\n";

	if (v1 != v3)
		std::cout << "not equal\n";
	else
		std::cout <<"equal\n";

	if (v2.empty())
		std::cout << "empty\n";
	else
		std::cout << "not empty\n";


	return 0;
}
