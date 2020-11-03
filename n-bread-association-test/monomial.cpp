#include "monomial.h"
#include <cmath>

Monomial::Monomial() : _coefficient{ 0 }, _order{ 0 }
{

}

Monomial::~Monomial()
{

}


void Monomial::Nospace(std::string& expr)
{
	std::string pattern = " ";
	std::string replace = "";
	std::string result = expr;
	std::string::size_type pos = 0;
	std::string::size_type offset = 0;

	while ((pos = result.find(pattern, offset)) != std::string::npos)
	{
		result.replace(result.begin() + pos, result.begin() + pos + pattern.size(), replace);
		offset = pos + replace.size();
	}

		expr=result;
		return 0;
}

Monomial::Monomial(std::string& expr)
{
	std::string copy_expr;
	copy_expr = expr;
	int size = copy_expr.length();


	std::string divide_copy_front, divide_copy_back;
	std::string temp = "";
	int i = 0;
	int j = 0;
	std::string expr_end(*copy_expr.end());

	while (temp != "x")
	{
		divide_copy_front[i] = expr[i];
		temp = expr[i];
		i++;
	}
	i = i + 2;
	while ( expr_end != temp)
	{
		divide_copy_back[j] = expr[i];
		temp = expr[i];
		i++;
		j++;

	}
	_coefficient = atoi(divide_copy_back.c_str());
	_order = atoi(divide_copy_front.c_str());


}

int Monomial::getValue(int x)
{
	return _coefficient * pow(x, _order);
}