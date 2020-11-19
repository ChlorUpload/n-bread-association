#ifndef __H_POLYNOMIAL__
#define __H_POLYNOMIAL__

#include <vector>
#include <string>

class Monomial;

class Polynomial
{
private:
	std::vector<Monomial> _monomials;

public:
	Polynomial();
	~Polynomial();

	Polynomial(const std::string& expr);

	int getValue(int x);

	Polynomial operator+(Polynomial& rhs);

	friend Polynomial operator+(Polynomial& lhs, Monomial& rhs);
	friend Polynomial operator+(Monomial& lhs, Polynomial& rhs);
};

#endif