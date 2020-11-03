#ifndef __H_POLYNOMIAL__
#define __H_POLYNOMIAL__

#include <vector>

#include "monomial.h"

class Polynomial
{
private:
	std::vector<Monomial> _monomials;

public:
	Polynomial();
	~Polynomial();

	Polynomial(std::string& expr);

	int getValue(int x);
};

#endif