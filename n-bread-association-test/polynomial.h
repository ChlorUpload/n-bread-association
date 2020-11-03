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

	Polynomial operator+(Monomial& rhs);
	Polynomial operator+(Polynomial& rhs);
	friend Polynomial operator+(Monomial& lhs, Polynomial& rhs);
};

#endif