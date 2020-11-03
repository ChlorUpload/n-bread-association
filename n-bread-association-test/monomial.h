#ifndef __H_MONOMIAL__
#define __H_MONOMIAL__

#include <string>

class Monomial
{
public:
	int _coefficient;
	int _order;

	Monomial();
	Monomial(int coefficient, int order);
	~Monomial();

	Monomial(std::string& expr);

	int getValue(int x);
};

#endif