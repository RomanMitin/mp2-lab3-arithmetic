// реализация пользовательского приложения
#include<iostream>
#include"..\\include\stack.h"
#include"..\\include\vector.h"
#include"..\\include\arithmetic.h"


int main()
{
	vector<token> tokens;
	vector<token> postfix;

	bool is_correct = false;
	std::string str;
	while (!is_correct)
	{
		std::cout << "Enter your exprecion\n";
		
		std::getline(std::cin, str);
		try
		{
			is_correct = correct(str);
		}
		catch (exception e)
		{
			std::cout << e.what() << " in symbol number " << e.index << '\n';
			is_correct = false;
		}
	}

	tokens = parcer(str);
	std::cout << "Input:\n";
	for (int i = 0; i < tokens.size(); i++)
		std::cout << tokens[i] << ' ';
	std::cout << "\n\n";

	std::cout << "Enter variable value\n";
	get_variables(tokens);

	postfix = to_polish(tokens);
	std::cout << "Postfix:\n";
	for (int i = 0; i < tokens.size(); i++)
		std::cout << tokens[i] << ' ';
	std::cout << "\n\n";

	double result = compute(postfix);

	std::cout << "Result is: " << result << '\n';
	return 0;
}
