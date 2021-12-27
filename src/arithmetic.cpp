// реализация функций и классов для вычисления арифметических выражений
#include"..\\include\arithmetic.h"

double operation::operator()(double a, double b)
{
	switch (this->op)
	{
	case add:
		return a + b;
		break;
	case sub:
		return a - b;
		break;
	case mul:
		return a * b;
		break;
	case divide:
		return a / b;
		break;
	}
}

operation::operation(char oper)
{
	switch (oper)
	{
	case '+':
		op = add;
		break;
	case '-':
		op = sub;
		break;
	case '*':
		op = mul;
		break;
	case '/':
		op = divide;
		break;
	default:
		break;
	}
}

std::ostream& operator<<(std::ostream& str, const operation oper)
{
	switch (oper.op)
	{
	case add:
		str << '+';
		break;
	case sub:
		str << '-';
		break;
	case mul:
		str << '*';
		break;
	case divide:
		str << '/';
		break;
	}
	return str;
}

std::ostream& operator<<(std::ostream& str, const bracket br)
{
	if (br.open)
		str << '(';
	else
		str << ')';
	return str;
}

token& token::operator=(const token& sec)
{
	if (this == &sec)
		return *this;

	type = sec.type;
	switch (type)
	{
	case Variable:
		var = sec.var;
		break;
	case Number:
		num = sec.num;
		break;
	case Operation:
		oper = sec.oper;
		break;
	case Bracket:
		brack = sec.brack;
		break;
	case Function:
		break;
	}
}

bool token::operator==(const token& sec) const
{
	if (type != sec.type)
		return false;
	switch (type)
	{
	case Variable:
		return var.name == sec.var.name && var.value == sec.var.value;
	case Number:
		return num.val == sec.num.val;
	case Operation:
		return oper.op == sec.oper.op;
	case Bracket:
		return brack.open == sec.brack.open;
	case Function:
		return true;
	}
}

bool token::operator!=(const token& sec) const
{
	return !(*this == sec);
}

std::ostream& operator<<(std::ostream& str, const token tok)
{
	switch (tok.type)
	{
	case Variable:
		str << tok.var;
		break;
	case Number:
		str << tok.num;
		break;
	case Operation:
		str << tok.oper;
		break;
	case Bracket:
		str << tok.brack;
		break;
	case Function:
		str << tok.func;
		break;
	}
	return str;
}

bool correct(std::string input)
{
	int count_brack = 0;
	int open_brack_ind = -1;
	bool is_open = false;
	bool dot = false;

	if (input.empty())
		return true;

	if (input[0] == ')' || operation() == input[0] && input[0] != '-')
		throw exception("Wrong beggining of the expretion", 0);

	for (int i = 0; i < input.size(); i++)
	{
		if (variable() != input[i] && number() != input[i] && operation() != input[i] && bracket() != input[i])
			throw exception("Wrong symbol", i);

		if (input[i] == '.' && !dot)
		{
			dot = true;
		}
		else
		{
			if (input[i] == '.')
				throw exception("Two dots in number", i);
		}

		if (number() != input[i])
			dot = false;

		if (bracket() == input[i])
		{
			if (input[i] == '(')
			{
				if (!count_brack)
					open_brack_ind = i;
				count_brack++;
				is_open = true;
			}
			else
			{
				if (count_brack == 0)
					throw exception("The opening parenthesis is missing", i);
				count_brack--;
				is_open = false;
			}
		}
		if (i != 0 && variable() == input[i] && variable() == input[i - 1])
			throw exception("Name for variable is too long, use one symbol for variable", i);

		if (i != 0 && bracket() == input[i] && (number() == input[i - 1] && variable() == input[i - 1]))
			throw exception("Bracket after number or variable", i);

		if (i != 0 && bracket() == input[i-1] && (number() == input[i] && variable() == input[i]))
			throw exception("Number or variable after bracket", i);

		if (i != 0 && (number() == input[i - 1] || variable() == input[i - 1]) && \
			operation() != input[i] && input[i] != ')' && number() != input[i])
			throw exception("Number or variable before bracket", i);

		if (i != 0 && (number() == input[i] || variable() == input[i]) && \
			operation() != input[i - 1] && input[i - 1] != '(' && number() != input[i - 1])
			throw exception("Number or variable after bracket", i);

		if (i != 0 && '-' == input[i - 1] && number() != input[i] && variable() != input[i] && bracket() != input[i] && '-' != input[i])
			throw exception("Not a number or bracket after -", i);

		if (i != 0 && operation() == input[i - 1] && (operation() == input[i] && '-' != input[i]))
			throw exception("Incorrect symbol after operation", i);

		if (i != 0 && input[i - 1] == '.' && (number() != input[i] || input[i] == '.'))
			throw exception("Number cant end with dot", i);
	}
	if (input[input.size() - 1] == '(' || operation() == input[input.size() - 1] || input[input.size() - 1] == '.')
		throw exception("Wrong ending of the expretion", input.size() - 1);

	if (count_brack)
		throw exception("The closing bracket is missing", open_brack_ind);

	return true;
}

token getnumber(std::string s, int& index)
{
	double result = 0.0;
	while (index < s.size() && s[index] >= '0' && s[index] <= '9')
	{
		result *= 10.0;
		result += s[index] - '0';
		index++;
	}

	if (s[index] == '.')
	{
		index++;
		double power = 0.1;
		while (index < s.size() && s[index] >= '0' && s[index] <= '9')
		{
			result += (s[index] - '0') * power;
			power *= 0.1;
			index++;
		}
	}
			
	token tmp;
	tmp.type = Number;
	tmp.num = number(result);
	return tmp;
}

int oper_priority(operation type)
{
	switch (type.op)
	{
	case add:
	case sub:
		return 2;
	case mul:
	case divide:
		return 1;
	}
}

int oper_priority(function)
{
	return 3;
}

vector<token> parcer(std::string input)
{
	vector<token> result;

	int index = 0;
	while (index != input.size())
	{
		if (number() == input[index])
			result.push_back(getnumber(input, index));
		if (index == input.size())
			break;

		if (variable() == input[index])
		{
			token tmp;
			tmp.var = variable(input[index++]);
			tmp.type = Variable;
			result.push_back(tmp);
		}
		if (index == input.size())
			break;

		if (bracket() == input[index])
		{
			token tmp;
			tmp.brack = bracket(input[index++] == '(');
			tmp.type = Bracket;
			result.push_back(tmp);
		}
		if (index == input.size())
			break;

		if (operation() == input[index])
		{
			token tmp;
			if (input[index] != '-')
			{
				tmp.type = Operation;
				tmp.oper = operation(input[index]);
			}
			else
			{
				if (index == 0 || input[index - 1] == '(' || operation() == input[index - 1])
				{
					tmp.type = Function;
				}
				else
				{
					tmp.type = Operation;
					tmp.oper = operation(input[index]);
				}
				
			}
			result.push_back(tmp);
			index++;
		}
	}

	return result;
}

vector<token> to_polish(vector<token> vec)
{
	vector<token> result;
	stack<token> st;

	for (int i = 0; i < vec.size(); i++)
	{
		switch (vec[i].type)
		{
		case Variable:
		case Number:
			result.push_back(vec[i]);
			break;
		case Operation:
			while (!st.is_empty() && st.top().type != Bracket\
				&& oper_priority(vec[i].oper) >= oper_priority(st.top().oper))
				result.push_back(st.pop());
			st.push_back(vec[i]);
			break;
		case Bracket:
			if (vec[i].brack.open)
			{
				st.push_back(vec[i]);
			}
			else
			{
				while (st.top().type != Bracket)
					result.push_back(st.pop());
				st.pop();
			}
			break;
		case Function:
			st.push_back(vec[i]);
		}
	}

	while (!st.is_empty())
	{
		result.push_back(st.pop());
	}

	return result;
}

bool check_names(vector<token*>& vars)
{
	for (int i = 0; i < vars.size(); i++)
		if (vars[i]->var.value == INFINITY)
			return false;
	return true;
}

void get_variables(vector<token>& tok)
{
	vector<token*> vars;

	for (int i = 0; i < tok.size(); i++)
		if (tok[i].type == Variable)
			vars.push_back(&tok[i]);

	std::string name;

	while (!check_names(vars))
	{
		std::getline(std::cin, name);
		if (variable() != name[0])
		{
			std::cout << "Wrong name for variable\n";
			continue;
		}
		int i = 1;
		double value;
		while (i < name.size() && name[i] == ' ' || name[i] == '=')
		{
			i++;
		}

		try 
		{
			correct(name.substr(i, name.size()));
		}
		catch(exception e)
		{
			std::cout << e.what() << ": " << e.index << '\n';
			continue;
		}

		bool minus = false;
		if (name[i] == '-')
		{
			minus = true;
			i++;
		}

		if (number() == name[i])
			value = getnumber(name, i).num.val;
		if (i != name.size())
		{
			std::cout << "Wrong symbol in number\n";
			continue;
		}

		if (minus)
			value *= -1;

		for (int i = 0; i < vars.size(); i++)
		{
			if (vars[i]->var.name == name[0])
			{
				vars[i]->var.value = value;
			}
		}
	}

}

double compute(vector<token> expr)
{
	if (expr.empty())
		return 0.0;

	stack<double> result;

	for (int i = 0; i < expr.size(); i++)
	{
		switch (expr[i].type)
		{
		case Variable:
			result.push_back(expr[i].var.value);
			break;
		case Number:
			result.push_back(expr[i].num.val);
			break;
		case Operation:
		{
			double tmp = result.pop();
			tmp = expr[i].oper.operator()(result.pop(), tmp);
			result.push_back(tmp);
			break;
		}
		case Function:
		{
			double tmp = result.pop();
			tmp *= -1;
			result.push_back(tmp);
			break;
		}
		default:
			break;
		}
	}
	return result.pop();
}

