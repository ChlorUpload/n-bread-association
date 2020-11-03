#include "polynomial.h"
#include "monomial.h"

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
	int PValue = 0; //°á°ú°ª
	for (Monomial &ele : _monomials)
	{
		PValue += ele.getValue(x);
	}
	return PValue;
}