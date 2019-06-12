#include <iostream>
#include <string.h>
#include "inpact.h"
using namespace std;

int main()
{
	inpact r("input.txt");
	double q=r.calculate();
	cout << q;
	return 0;
}