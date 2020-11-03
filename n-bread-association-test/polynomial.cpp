#include "polynomial.h"

Polynomial::Polynomial()
{

}

Polynomial::~Polynomial()
{

}

Polynomial::Polynomial(std::string& expr)
{

}

int Polynomial::getValue(int x)
{
	int value = 0; //�����
	for (Monomial &elem : _monomials)
	{
		value += elem.getValue(x);
	}
	return value;
}

Polynomial Polynomial::operator+(Monomial& rhs)
{
	for (Monomial& elem : _monomials)
	{
		if (elem._order == rhs._order)
		{
			elem._coefficient += rhs._coefficient;
			return *this;
		}
	}
	_monomials.push_back(rhs);
	return *this;
}

Polynomial operator+(Monomial& lhs, Polynomial& rhs)
{
	Polynomial ret;
	for (Monomial& elem : rhs._monomials)
	{
		if (elem._order == lhs._order)
		{
			Monomial temp {
				elem._coefficient + lhs._coefficient,
				elem._order 
			};
			ret._monomials.push_back(temp);
		}
		else
		{
			ret._monomials.push_back(elem);
		}
	}
	
	return ret;
}

Polynomial Polynomial::operator+(Polynomial& rhs)
{
	for (Monomial& elem : rhs._monomials)
	{
		*this = *this + elem;
	}

	return *this;
}
