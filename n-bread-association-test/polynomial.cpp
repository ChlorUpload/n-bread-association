#include "polynomial.h"
#include "monomial.h"

Polynomial::Polynomial()
{
	_monomials.push_back(Monomial());
}

Polynomial::~Polynomial()
{

}

Polynomial::Polynomial(std::string& expr)
{
	std::string temp;
	for(int i=0; i < expr.length(); i++)
	{
		if (expr[i] == '+' or expr[i] == '-')
		{
			_monomials.push_back(Monomial(temp));
			temp.empty();
		}
		temp.push_back(expr[i]);
	}
	_monomials.push_back(Monomial(temp));
}

int Polynomial::getValue(int x)
{
	return 0;
}