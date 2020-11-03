#ifndef __H_MONOMIAL__
#define __H_MONOMIAL__

#include <string>

class Polynomial;

class Monomial
{
private:
	int _coefficient;
	int _order;

	void removeSpace(std::string& expr);
public:
	Monomial();
	Monomial(int coefficient, int order);
	~Monomial();
	Monomial(const std::string& expr);

	int getValue(int x);

	friend Polynomial operator+(Polynomial& lhs, Monomial& rhs);
	friend Polynomial operator+(Monomial& lhs, Polynomial& rhs);
};

#endif