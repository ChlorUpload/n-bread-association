#include "polynomial.h"
#include <cmath>

Monomial::Monomial() : _coefficient{ 0 }, _order{ 0 }
{

}

Monomial::Monomial(int coefficient, int order) : _coefficient(coefficient), _order(order)
{

}

Monomial::~Monomial()
{

}

Monomial::Monomial(std::string& expr)
{
	_coefficient = 0;
	_order = 0;
}

int Monomial::getValue(int x)
{
	return _coefficient * pow(x, _order);
}