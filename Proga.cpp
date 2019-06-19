#include <iostream>
#include <string.h>
#include "inpact.h"
#include <conio.h>
using namespace std;

int main()
{
	inpact r("input.txt");
	double q = r.calculate();
	cout << endl << "q =  " << q << endl;
	_getch();
	return 0;
}
