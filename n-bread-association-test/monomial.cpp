#include <cmath>

#include "monomial.h"

Monomial::Monomial() : _coefficient{ 0 }, _order{ 0 }
{

}

Monomial::Monomial(int coefficient, int order) : _coefficient(coefficient), _order(order)
{

}

Monomial::~Monomial()
{

}


void Monomial::removeSpace(std::string& expr)
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
}

Monomial::Monomial(const std::string& expr)
{
	std::string copy_expr = expr;
	removeSpace(copy_expr);

	std::string divide_copy_front, divide_copy_back;

	std::string::size_type pos = copy_expr.find("x", 0);

	// 상수항
	if (pos == std::string::npos)
	{
		_coefficient = std::atoi(copy_expr.c_str());
		_order = 0;
		return;
	}

	divide_copy_front = copy_expr.substr(0, pos);
	divide_copy_back = copy_expr.substr(pos + 1, std::string::npos);

	if (divide_copy_back[0] == '^')
	{
		// ^ 표시가 있으므로 차수가 2 이상
		divide_copy_back = divide_copy_back.substr(1, std::string::npos);
		_coefficient = atoi(divide_copy_front.c_str());
		_order = atoi(divide_copy_back.c_str());
	}
	else
	{
		// 차수가 1
		_coefficient = atoi(divide_copy_front.c_str());
		_order = 1;
	}
	
}

int Monomial::getValue(int x)
{
	return _coefficient * pow(x, _order);
}