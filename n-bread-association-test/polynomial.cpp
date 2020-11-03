#include "polynomial.h"
#include "monomial.h"

Polynomial::Polynomial()
{
}

Polynomial::~Polynomial()
{

}

Polynomial::Polynomial(const std::string& expr)
{
	std::string temp;
	for(int i=0; i < expr.length(); i++)
	{
		if (expr[i] == '+' || expr[i] == '-')
		{
			if(!temp.empty()) _monomials.push_back(Monomial(temp));
			temp.clear();
		}
		if(expr[i] != ' ') temp.push_back(expr[i]);
	}
	_monomials.push_back(Monomial(temp));
}

int Polynomial::getValue(int x)
{
	int value = 0; //°á°ú°ª

	if (_monomials.empty()) return 0;

	for (Monomial &elem : _monomials)
	{
		value += elem.getValue(x);
	}
	return value;
}

Polynomial operator+(Polynomial& lhs, Monomial& rhs)
{
	Polynomial ret;
	for (Monomial& elem : lhs._monomials)
	{
		if (elem._order == rhs._order)
		{
			Monomial temp{
				elem._coefficient + rhs._coefficient,
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
	Polynomial ret = *this;
	for (Monomial& elem : rhs._monomials)
	{
		ret = ret + elem;
	}

	return ret;
}
