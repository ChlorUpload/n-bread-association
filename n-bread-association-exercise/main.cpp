#include <iostream>

#include "polynomial.h"
#include "monomial.h"

using namespace std;

int main(void)
{
	Polynomial p1(" - 35 x^ 3  +  3x ^2   - 10x + 3");
	Monomial m1(" 1 0x");

	Polynomial p2 = p1 + m1;

	Polynomial p3 = p1 + p2;

	Polynomial p4 = m1 + p1;

	cout << p2.getValue(-1) << endl;
}