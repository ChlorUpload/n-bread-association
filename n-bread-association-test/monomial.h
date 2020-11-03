#ifndef __H_MONOMIAL__
#define __H_MONOMIAL__

#include <string>

class Monomial
{
private:
	int _coefficient;
	int _order;


public:
	Monomial();
	Monomial(int coefficient, int order);
	~Monomial();
	Monomial(std::string& expr);
	
	void Nospace(std::string& expr);

	int getValue(int x);
};

#endif